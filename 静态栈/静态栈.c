#define Max_Size 100
 
typedef char DataType;
 
typedef struct                                  //自定义结构体stack
{
    DataType _Stack[Max_Size];
    DataType _top;
} Stack;

void StackInit(Stack* s);                        // 栈的初始化
void StackPush(Stack* s, DataType data);         // 入栈
DataType StackTop(Stack* s);                     // 出栈
int StackSize(Stack* s);                         // 获取栈顶元素
void StackPop(Stack* s);                         // 获取栈中元素个数
int StackEmpty(Stack* s);                        // 检测栈是否为空
void Print(Stack* s);                            // 打印栈顶元素

void StackInit(Stack* s)                        // 栈的初始化
{
    assert(s);        // 断言栈的地址有效
    s->_top = 0;
}
 
void StackPush(Stack* s, DataType data)         // 入栈
{
    assert(s);
    if (s->_top == Max_Size) {
        printf("栈已满\n");
        return;
    }
    s->_Stack[s->_top] = data;
    s->_top++;
}
 
DataType StackTop(Stack* s)                     // 出栈
{
    assert(s);
    if (s->_top != 0) {
        return (s->_Stack[s->_top - 1]);
    }
    printf("栈为空\n");
    return 0;
}
 
int StackSize(Stack* s)                         // 获取栈顶元素
{
    assert(s);
    return s->_top;
}
 
void StackPop(Stack* s)                         // 获取栈中元素个数
{
    assert(s);
    if (s->_top) {
        s->_top--;
        return;
    }
    printf("栈已空\n");
}
 
int StackEmpty(Stack* s)                        // 检测栈是否为空
{
    assert(s);
    return (0 == s->_top);
}
 
void Print(Stack* s)                            // 打印栈顶元素
{
    printf("%d\n",s->_Stack[s->_top - 1]);
}

int Bracket(char ch)            //用来检测当前字符是否是括号
{
    if (ch == '(' || ch == '[' || ch == '{') {
        return 1;       //标记1为左括号
    }else if (ch == ')' || ch == ']' || ch == '}'){
        return 2;       //标记2为右括号
    }
    return 0;
}
 
void MatchBrackets(const char* str)
{
    Stack s;
    StackInit(&s);      //建立一个栈并初始化
    if (NULL == str) {
        return;
    }
    
    int len = 0;
    int flag = 0;       //用来接收Bracket函数的返回值
    len = (int)strlen(str);
    
    for (int i=0; i<len; i++) {
        if ((flag = Bracket(str[i]))) {     //判断是否是括号，如果是进行下一步处理
            switch (flag) {
                case 1:             //左括号，直接压栈
                    StackPush(&s, str[i]);
                    break;
                case 2:             //右括号，判断是否与当前栈顶括号匹配
                    if (StackEmpty(&s)) {
                        printf("右括号多于左括号\n");   //栈为空，右括号多于左括号
                        return;
                    }
                    char top = StackTop(&s);
                    if (str[i] == ')') {
                        if (top != '(') {
                            printf("左右括号不匹配\n");    //栈顶括号与当前括号不匹配
                            return;
                        }
                    }
                    if (str[i] == ']') {
                        if (top != '[') {
                            printf("左右括号不匹配\n");
                            return;
                        }
                    }
                    if (str[i] == '}') {
                        if (top != '{') {
                            printf("左右括号不匹配\n");
                            return;
                        }
                    }
                    StackPop(&s);
                    break;
            }
        }
    }
    if (!StackEmpty(&s)) {
        printf("左括号多于右括号\n");       //如果字符串处理完毕，栈内仍有括号，则左括号多于右括号
        return;
    }
    printf("括号匹配：)\n");         //无误，括号匹配
}

int main()
{
    char a[] = "(())abc{[(])}";     // 左右括号次序匹配不正确
    char b[] = "(()))abc{[]}";      // 右括号多于左括号
    char c[] = "(()()abc{[]}";      // 左括号多于右括号
    char d[] = "(())abc{[]()}";     // 左右括号匹配正确
    MatchBrackets(a);
    MatchBrackets(b);
    MatchBrackets(c);
    MatchBrackets(d);
    
    return 0;
}
