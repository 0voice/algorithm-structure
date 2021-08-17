package com.oracle.moviecf;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;/**
 * 相似度
 * 与Job4同用
 * 根据 用户对特征的偏好权重矩阵 与 电影特征建模矩阵 ，求用户对电影的余弦相似度，即得到每个用户对每个电影的喜欢程度
 * 
 * */
public class Job3 {
	public static class Map extends Mapper&lt;LongWritable, Text, Text, Text&gt; {
		@Override
		protected void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			
			String line = value.toString();
			String split[] = line.split("\t");
			String userID = split[0];
			String tagID;
			double val;
			double a = 0;	//分母
			
			for(int i = 1; i &lt; split.length; i++) {
				val = Double.parseDouble(split[i].substring(split[i].indexOf("_")+1));
				a += val*val;
			}
			
			for(int i = 1; i &lt; split.length; i++) {
				tagID = split[i].substring(0, split[i].indexOf("_"));
				val = Double.parseDouble(split[i].substring(split[i].indexOf("_")+1));
				context.write(new Text(tagID), new Text(userID+"_"+val+"_"+a));
			}
		}
	}
	
	public static class Reduce extends Reducer&lt;Text, Text, Text, Text&gt; {
		@Override
		protected void reduce(Text key, Iterable&lt;Text&gt; values, Context context)
				throws IOException, InterruptedException {
			
			
			List&lt;String&gt; list_user = new ArrayList&lt;&gt;();
			List&lt;String&gt; list_movie = new ArrayList&lt;&gt;();
			String user_a;
			String mv_a;
			double user_val;
			double mv_val;
			String userID;
			String mvID;
			
			for(Text i: values) {
				if(i.toString().startsWith("u")) {
					list_user.add(i.toString());
				}else {
					list_movie.add(i.toString());
				}
			}
			
			String split[];
			for(String i: list_user) {
				split = i.split("_");
				userID = split[0];
				user_val = Double.parseDouble(split[1]);
				user_a = split[2];
				for(String j: list_movie) {
					split = j.split("_");
					mvID = split[0];
					mv_val = Double.parseDouble(split[1]);
					mv_a = split[2];
					context.write(new Text(userID+"_"+mvID), new Text((mv_val*user_val)+"_"+user_a+"_"+mv_a));
				}
			}
			
		
			
		/*for(Text i: values) {
			context.write(key, i);
		}*/
			
		}
	}
	
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		
		Job job = Job.getInstance(conf);
		job.setJarByClass(Job3.class);
		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);
		
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		
		
		FileInputFormat.setInputPaths(job, new Path("/moviecf/output2"));
		FileInputFormat.addInputPath(job, new Path("/moviecf/input/data1.txt"));
		FileOutputFormat.setOutputPath(job, new Path("/moviecf/output3"));
		
		job.waitForCompletion(true);
	}
}
