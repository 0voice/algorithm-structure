package com.oracle.moviecf;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
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
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

/**
 * 与Job1共同完成
 * 目的：
 * 	用户对电影的评价矩阵 × 电影特征建模矩阵 = 用户对某种特征的偏好权重
 * */
public class Job2 {
	public static class Map extends Mapper&lt;LongWritable, Text, Text, Text&gt; {
		@Override
		protected void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			
			String line = value.toString();
			String split[] = line.split("\t");
			String userID;
			String tagID;
			
			userID = split[0].substring(0, split[0].indexOf("_"));
			tagID = split[0].substring(split[0].indexOf("_")+1);
			context.write(new Text(userID), new Text(tagID+"_"+split[1]));
		}
	}
	
	public static class Reduce extends Reducer&lt;Text, Text, Text, Text&gt; {
		@Override
		protected void reduce(Text key, Iterable&lt;Text&gt; values, Context context)
				throws IOException, InterruptedException {
			
			HashMap&lt;String, Double&gt; map = new HashMap&lt;&gt;();
			List&lt;String&gt; list = new ArrayList&lt;&gt;();
			String tagID;
			double val;
			
			for(Text i: values) {
				tagID = i.toString().substring(0, i.toString().indexOf("_"));
				val = Double.parseDouble(i.toString().substring(i.toString().indexOf("_")+1));
				if(!map.containsKey(tagID)) {
					map.put(tagID, val);
					list.add(tagID);
				}else {
					map.put(tagID, val+map.get(tagID));
				}
			}
			
			StringBuffer line = new StringBuffer();
			Collections.sort(list);
			for(String i: list) {
				line.append(i+"_"+map.get(i)+"\t");
			}
			
			context.write(key, new Text(line.toString()));
		}
	}
	
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		
		Job job = Job.getInstance(conf);
		job.setJarByClass(Job2.class);
		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);
		
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		
		FileInputFormat.setInputPaths(job, new Path("/moviecf/output1"));
		FileOutputFormat.setOutputPath(job, new Path("/moviecf/output2"));
		
		job.waitForCompletion(true);
	}
}
