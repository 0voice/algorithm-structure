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
 * 与Job3同用
 * 根据 用户对特征的偏好权重矩阵 与 电影特征建模矩阵 ，求用户对电影的余弦相似度，即得到每个用户对每个电影的喜欢程度
 * */

public class Job4 {
	public static class Map extends Mapper&lt;LongWritable, Text, Text, Text&gt; {
		@Override
		protected void map(LongWritable key, Text value, Context context)
				throws IOException, InterruptedException {
			String line = value.toString();
			String split[] = line.split("\t");
			String userID = line.substring(0, line.indexOf("_"));
			String mvID = split[0].substring(split[0].indexOf("_")+1);
			
			context.write(new Text(userID), new Text(mvID+"\t"+split[1]));
		}
	}
	
	public static class Reduce extends Reducer&lt;Text, Text, Text, Text&gt; {
		@Override
		protected void reduce(Text key, Iterable&lt;Text&gt; values, Context context)
				throws IOException, InterruptedException {
			HashMap&lt;String, Double&gt; map_a = new HashMap&lt;&gt;();
			HashMap&lt;String, Double&gt; map_b = new HashMap&lt;&gt;();
			List&lt;String&gt; keyList = new ArrayList&lt;&gt;();
			
			String[] split;
			String[] stemp;
			double a;
			double b;
			for(Text i: values) {
				split = i.toString().split("\t");
				stemp = split[1].split("_");
				a = Math.sqrt(Double.parseDouble(stemp[1])*Double.parseDouble(stemp[2]));
				b = Double.parseDouble(stemp[0]);
				if(!map_a.containsKey(split[0])) {
					map_a.put(split[0], a);
					map_b.put(split[0], b);
					keyList.add(split[0]);
				}else {
					map_b.put(split[0], b+map_b.get(split[0]));
				}
			}
			
			Collections.sort(keyList);
			StringBuffer result = new StringBuffer();
			String userID = key.toString();
			double val;
			for(String i: keyList) {
				val = map_b.get(i) / map_a.get(i);
				result.append(i+"_"+String.format("%.1f", val)+"\t");
			}
			context.write(key, new Text(result.toString()));
		}
	}
	
	public static void main(String[] args) throws Exception {
	Configuration conf = new Configuration();
		
		Job job = Job.getInstance(conf);
		job.setJarByClass(Job4.class);
		job.setMapperClass(Map.class);
		job.setReducerClass(Reduce.class);
		
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		
		
		FileInputFormat.setInputPaths(job, new Path("/moviecf/output3"));
		FileOutputFormat.setOutputPath(job, new Path("/moviecf/output4"));
		
		job.waitForCompletion(true);
	}
}
