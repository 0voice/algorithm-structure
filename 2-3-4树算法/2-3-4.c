public class Tree234 {
    private Node root = new Node() ;
    /*public Tree234(){
        root = new Node();
    }*/
    //查找关键字值
    public int find(long key){
        Node curNode = root;
        int childNumber ;
        while(true){
            if((childNumber = curNode.findItem(key))!=-1){
                return childNumber;
            }else if(curNode.isLeaf()){//节点是叶节点
                return -1;
            }else{
                curNode = getNextChild(curNode,key);
            }
        }
    }
     
    public Node getNextChild(Node theNode,long theValue){
        int j;
        int numItems = theNode.getNumItems();
        for(j = 0 ; j < numItems ; j++){
            if(theValue < theNode.getItem(j).dData){
                return theNode.getChild(j);
            }
        }
        return theNode.getChild(j);
    }
     
    //插入数据项
    public void insert(long dValue){
        Node curNode = root;
        DataItem tempItem = new DataItem(dValue);
        while(true){
            if(curNode.isFull()){//如果节点满数据项了，则分裂节点
                split(curNode);
                curNode = curNode.getParent();
                curNode = getNextChild(curNode, dValue);
            }else if(curNode.isLeaf()){//当前节点是叶节点
                break;
            }else{
                curNode = getNextChild(curNode, dValue);
            }
        }//end while
        curNode.insertItem(tempItem);
    }
     
    public void split(Node thisNode){
        DataItem itemB,itemC;
        Node parent,child2,child3;
        int itemIndex;
        itemC = thisNode.removeItem();
        itemB = thisNode.removeItem();
        child2 = thisNode.disconnectChild(2);
        child3 = thisNode.disconnectChild(3);
        Node newRight = new Node();
        if(thisNode == root){//如果当前节点是根节点，执行根分裂
            root = new Node();
            parent = root;
            root.connectChild(0, thisNode);
        }else{
            parent = thisNode.getParent();
        }
        //处理父节点
        itemIndex = parent.insertItem(itemB);
        int n = parent.getNumItems();
        for(int j = n-1; j > itemIndex ; j--){
            Node temp = parent.disconnectChild(j);
            parent.connectChild(j+1, temp);
        }
        parent.connectChild(itemIndex+1, newRight);
         
        //处理新建的右节点
        newRight.insertItem(itemC);
        newRight.connectChild(0, child2);
        newRight.connectChild(1, child3);
    }
     
    //打印树节点
    public void displayTree(){
        recDisplayTree(root,0,0);
    }
    private void recDisplayTree(Node thisNode,int level,int childNumber){
        System.out.println("levle="+level+" child="+childNumber+" ");
        thisNode.displayNode();
        int numItems = thisNode.getNumItems();
        for(int j = 0; j < numItems+1 ; j++){
            Node nextNode = thisNode.getChild(j);
            if(nextNode != null){
                recDisplayTree(nextNode, level+1, j);
            }else{
                return;
            }
        }
    }
 
    //数据项
    class DataItem{
        public long dData;
        public DataItem(long dData){
            this.dData = dData;
        }
        public void displayItem(){
            System.out.println("/"+dData);
        }
    }
     
    //节点
    class Node{
        private static final int ORDER = 4;
        private int numItems;//表示该节点有多少个数据项
        private Node parent;//父节点
        private Node childArray[] = new Node[ORDER];//存储子节点的数组，最多有4个子节点
        private DataItem itemArray[] = new DataItem[ORDER-1];//存放数据项的数组，一个节点最多有三个数据项
         
        //连接子节点
        public void connectChild(int childNum,Node child){
            childArray[childNum] = child;
            if(child != null){
                child.parent = this;
            }
        }
        //断开与子节点的连接，并返回该子节点
        public Node disconnectChild(int childNum){
            Node tempNode = childArray[childNum];
            childArray[childNum] = null;
            return tempNode;
        }
        //得到节点的某个子节点
        public Node getChild(int childNum){
            return childArray[childNum];
        }
        //得到父节点
        public Node getParent(){
            return parent;
        }
        //判断是否是叶节点
        public boolean isLeaf(){
            return (childArray[0] == null)?true:false;
        }
        //得到节点数据项的个数
        public int getNumItems(){
            return numItems;
        }
        //得到节点的某个数据项
        public DataItem getItem(int index){
            return itemArray[index];
        }
        //判断节点的数据项是否满了（最多3个）
        public boolean isFull(){
            return (numItems == ORDER-1) ? true:false;
        }
         
        //找到数据项在节点中的位置
        public int findItem(long key){
            for(int j = 0 ; j < ORDER-1 ; j++){
                if(itemArray[j]==null){
                    break;
                }else if(itemArray[j].dData == key){
                    return j;
                }
            }
            return -1;
        }
         
        //将数据项插入到节点
        public int insertItem(DataItem newItem){
            numItems++;
            long newKey = newItem.dData;
            for(int j = ORDER-2 ; j >= 0 ; j--){
                if(itemArray[j] == null){//如果为空，继续向前循环
                    continue;
                }else{
                    long itsKey = itemArray[j].dData;//保存节点某个位置的数据项
                    if(newKey < itsKey){//如果比新插入的数据项大
                        itemArray[j+1] = itemArray[j];//将大数据项向后移动一位
                    }else{
                        itemArray[j+1] = newItem;//如果比新插入的数据项小，则直接插入
                        return j+1;
                    }
                }
            }
            //如果都为空，或者都比待插入的数据项大，则将待插入的数据项放在节点第一个位置
            itemArray[0] = newItem;
            return 0;
        }
        //移除节点的数据项
        public DataItem removeItem(){
            DataItem temp = itemArray[numItems-1];
            itemArray[numItems-1] = null;
            numItems--;
            return temp;
        }
        //打印节点的所有数据项
        public void displayNode(){
            for(int j = 0 ; j < numItems ; j++){
                itemArray[j].displayItem();
            }
            System.out.println("/");
        }
    }
}
