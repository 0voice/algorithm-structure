    //一次点击率可以增加的得分
    private static int READ_COUNT_K = 1;
    //一次点赞增加的评分
    private static int LIKE_COUNT_K = 3;

  public double calculateHackerNewsScore(Article article)
    {
        String updateTime = article.getUpdateTime();
        int readCount = article.getReadCount();
        int likeCount = article.getLikeCount();
        SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        Date date = null;
        try {
            date = formatter.parse(updateTime);
        } catch (ParseException e) {
            date = new Date();
        }

        //发帖时间的时间戳
        double updateTimeStamp = date.getTime() ;
        System.out.println("发帖时间的时间戳"+updateTimeStamp);
        //当前时间的时间戳
        double nowTimeStamp = System.currentTimeMillis();
        System.out.println("当前时间的时间戳"+nowTimeStamp);
        //用来获取两个时间相差的毫秒数
        double l=nowTimeStamp -updateTimeStamp;

        //相差的天
        double day=l/(24*60*60*1000);
        //相差的小时
        double hour=(day*24);

        double week = day/7;
        double month = week/4;
        /**
         * HackerNews评分   分子  点击权重为1    点赞权重为3    分母为 距离发帖时间相差的时间+2的G次方
         */
        double score =  ((readCount *READ_COUNT_K + likeCount *LIKE_COUNT_K) -1)/Math.pow((week +2),G);
        score *= 10000;
        System.out.println("文章" +article.getId() +"    发帖时间为" +updateTime +"    与当前时间相差" + week +"星期     评分为"+score);
        return score;
    }

