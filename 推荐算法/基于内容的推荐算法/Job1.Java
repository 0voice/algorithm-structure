package com.oracle.moviecf;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

/**
 * 与Job2共同完成：
 * 	用户对电影的评价矩阵 × 电影特征建模矩阵 = 用户对某种特征的偏好权重
 * （矩阵的相乘）
 * */
public class Job1 {
	public static class Map extends Mapper&lt;LongWritable, Text, Text, Text&gt; {
		@Override
		protected void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			String line = value.toString();
			String split[];
			String val;
			String mvID;
			String userID;
			
			if(line.startsWith("u")) {
				split = line.split("\t");
				userID = split[0];
				for(int i = 1; i &lt; split.length; i++) {
					val = split[i].substring(split[i].indexOf("_")+1);
					mvID = split[i].substring(0, split[i].indexOf("_"));
					context.write(new Text(mvID), new Text(userID+"_"+val));
				}
			}
			if(line.startsWith("m")) {
				split = line.split("\t");
				for(int i = 1; i &lt; split.length; i++) {
					context.write(new Text(split[0]), new Text(split[i]));
				}
			}
			
		}
	}
	
	public static class Reduce extends Reducer&lt;Text, Text, Text, Text&gt; {
		@Override
		protected void reduce(Text key, Iterable&lt;Text&gt; values, Context context)
				throws IOException, InterruptedException {
			List&lt;String&gt; list_user_val = new ArrayList&lt;&gt;();
			List&lt;String&gt; list_tag_val = new ArrayList&lt;&gt;();
			for(Text i: values) {
				if(i.toString().startsWith("u")) {
					list_user_val.add(i.toString());
				}else {
					list_tag_val.add(i.toString());
				}
			}
			
			String userID;
			double userVal;
			String tagID;
			double tagVal;
			for(String i: list_user_val) {
				userID = i.substring(0, i.indexOf("_"));
				userVal = Double.parseDouble(i.substring(i.indexOf("_")+1));
				for(String j: list_tag_val) {
					tagID = j.substring(0, j.indexOf("_"));
					tagVal = Double.parseDouble(j.substring(j.indexOf("_")+1));
					context.write(new Text(userID+"_"+tagID), new Text(String.valueOf(userVal*tagVal)));
				}
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		
		Job job = Job.getInstance(conf);
		job.setJarByClass(Job1.class);
		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);
		
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		
		FileInputFormat.setInputPaths(job, new Path("/moviecf/input"));
		FileOutputFormat.setOutputPath(job, new Path("/moviecf/output1"));
		
		job.waitForCompletion(true);
	}
}
