#include <stdio.h>
#include <stdlib.h>

enum return_result {EMPTY_OK = 100, EMPTY_NO, PUSH_OK, PUSH_NO, POP_OK, POP_NO};

typedef struct node
{
    int data;
    struct node * next;
}Node, *Link;//链结构

typedef struct stk
{
    Link space;
}Stack;//栈结构

/*malloc是否正确执行*/
void is_malloc_ok(void * node)
{
    if (node == NULL)
    {
        printf("malloc error!\n");
        exit(-1);
    }
}

/*创建一个栈*/
void create_stack(Stack ** stack)
{
    *stack = (Stack *)malloc(sizeof(Stack));
    is_malloc_ok(*stack);
    (*stack)->space = (Link)malloc(sizeof(Node));
    is_malloc_ok((*stack)->space);
}

/*初始化栈*/
void init_stack(Stack *stack)
{
    stack->space->next = NULL;
}

/*创建一个压栈元素*/
void create_node(Link * new_node)
{
    *new_node = (Link)malloc(sizeof(Node));
    is_malloc_ok(*new_node);
}

/*压栈*/
void push_stack(Stack *stack, Link new_node)
{
    new_node->next = stack->space->next;
    stack->space->next = new_node;
}

/*判断栈空*/
int is_stack_empty(Stack *stack)
{
    Link p = NULL;

    p = stack->space->next;

    if (p == NULL)
    {
        return EMPTY_OK;
    }

    return EMPTY_NO;
}

/*出栈*/
int pop_stack(Stack *stack)
{
    Link p = NULL;
    int data;

    if (stack == NULL)
    {//栈不存在
        printf("stack is not exist!\n");
        exit(-1);
    }

    if (EMPTY_OK == is_stack_empty(stack))
    {
        printf("stack is empty!\n");
        return POP_NO;
    }
    p = stack->space->next;
    stack->space->next = p->next;

    data = p->data;

    free(p);//释放栈顶

    return data;
}

/**/
void release_stack(Stack **stack)
{
    Link p = NULL;

    if (EMPTY_NO == is_stack_empty(*stack))
    {//栈不空
        p = (*stack)->space->next;

        while ((*stack)->space->next != NULL)
        {
            (*stack)->space->next = p->next;
            free(p);
            p = (*stack)->space->next;
        }
    }
    free((*stack)->space);//链头结点
    free(*stack);//释放栈
    *stack = NULL;
}

int main()
{
    int i;
    int ret;
    Stack *stack = NULL;
    Link new_node = NULL;//入栈新元素

    create_stack(&stack);

    init_stack(stack);

    for (i = 0; i < 10; i++)
    {//入栈
        create_node(&new_node);
        new_node->data = i + 1;
        push_stack(stack, new_node);//相当于链表的头插
    }

    for (i = 0; i < 5; i++)
    {//出栈
        ret = pop_stack(stack);

        if (ret == POP_NO)
        {
            break;
        }
        printf("%d\n", ret);
    }

    release_stack(&stack);
    pop_stack(stack);
    return 0;
}
