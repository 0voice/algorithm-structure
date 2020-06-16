

#include "xrbtree.h"

#include <stdlib.h>
#include <memory.h>


#ifndef ENABLE_XASSERT
#if ((defined _DEBUG) || (defined DEBUG))
#define ENABLE_XASSERT 1
#else 
#define ENABLE_XASSERT 0
#endif 
#endif 

#ifndef XASSERT
#if ENABLE_XASSERT
#include <assert.h>
#define XASSERT(xptr)    assert(xptr)
#else 
#define XASSERT(xptr)
#endif 
#endif 


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif 

typedef xrbt_byte_t xrbt_vkey_ptr;


typedef struct x_rbtree_node_t
{
    xrbt_uint32_t xut_color :  1;  
    xrbt_uint32_t xut_ksize : 31; 
    x_rbnode_iter xiter_parent;    
    x_rbnode_iter xiter_left;      
    x_rbnode_iter xiter_right;     

#ifdef _MSC_VER
#pragma warning(disable:4200)
#endif 
    xrbt_vkey_ptr xvkey_ptr[0];      
#ifdef _MSC_VER
#pragma warning(default:4200)
#endif 

} x_rbtree_node_t;


typedef struct x_rbtree_nil_t
{
    xrbt_uint32_t xut_color :  1;  
    xrbt_uint32_t xut_ksize : 31;  
    x_rbnode_iter xiter_parent;
    x_rbnode_iter xiter_left;      
    x_rbnode_iter xiter_right;     
    x_rbtree_ptr  xower_ptr;       
} x_rbtree_nil_t;


typedef struct x_rbtree_t
{
    xrbt_size_t      xst_ksize;     
    xrbt_callback_t  xcallback;     
    xrbt_size_t      xst_count;     
    x_rbtree_nil_t   xnode_nil;     
    x_rbnode_iter    xiter_root;    
    x_rbnode_iter    xiter_lnode;   
    x_rbnode_iter    xiter_rnode;   
} x_rbtree_t;

#define X_RED    0
#define X_BLACK  1

#define XNODE_SPIN_CLR(xiter_node)  ((xiter_node)->xut_color = !(xiter_node)->xut_color)
#define XNODE_VKEY(xiter_node)      ((xrbt_vkey_t)((xiter_node)->xvkey_ptr))
#define XNODE_IS_NIL(xiter_node)    (0 == (xiter_node)->xut_ksize)
#define XNODE_NOT_NIL(xiter_node)   (0 != (xiter_node)->xut_ksize)

#define XNODE_IS_DOCKED(xiter_node)                       \
            ((XRBT_NULL != (xiter_node)->xiter_parent) && \
             (XRBT_NULL != (xiter_node)->xiter_left  ) && \
             (XRBT_NULL != (xiter_node)->xiter_right ))   \

#define XNODE_IS_UNDOCKED(xiter_node)                     \
            ((XRBT_NULL == (xiter_node)->xiter_parent) && \
             (XRBT_NULL == (xiter_node)->xiter_left  ) && \
             (XRBT_NULL == (xiter_node)->xiter_right ))   \

#define XNODE_UNDOCK(xiter_node)                          \
            do                                            \
            {                                             \
                (xiter_node)->xiter_parent = XRBT_NULL;   \
                (xiter_node)->xiter_left   = XRBT_NULL;   \
                (xiter_node)->xiter_right  = XRBT_NULL;   \
            } while (0)                                   \

#define XTREE_BEGIN(xtree_ptr)      ((xtree_ptr)->xiter_lnode)
#define XTREE_RBEGIN(xtree_ptr)     ((xtree_ptr)->xiter_rnode)
#define XTREE_GET_NIL(xtree_ptr)    ((x_rbnode_iter)(&(xtree_ptr)->xnode_nil))
#define XTREE_SET_NIL(xtree_ptr, xiter_node) \
            ((xiter_node) = (x_rbnode_iter)(&(xtree_ptr)->xnode_nil))

#define X_RESET_NIL(xtree_ptr)                                                 \
            do                                                                 \
            {                                                                  \
                (xtree_ptr)->xnode_nil.xut_color = X_BLACK;                    \
                (xtree_ptr)->xnode_nil.xut_ksize = 0;                          \
                XTREE_SET_NIL(xtree_ptr, (xtree_ptr)->xnode_nil.xiter_parent); \
                XTREE_SET_NIL(xtree_ptr, (xtree_ptr)->xnode_nil.xiter_left  ); \
                XTREE_SET_NIL(xtree_ptr, (xtree_ptr)->xnode_nil.xiter_right ); \
                (xtree_ptr)->xnode_nil.xower_ptr = (xtree_ptr);                \
            } while (0)                                                        \




static inline xrbt_void_t * xrbt_heap_alloc(xrbt_size_t xst_size)
{
    return malloc(xst_size);
}


static inline xrbt_void_t xrbt_heap_free(xrbt_void_t * xmt_heap)
{
    if (XRBT_NULL != xmt_heap)
        free(xmt_heap);
}



static xrbt_void_t * xrbt_comm_node_memalloc(
                                xrbt_vkey_t xrbt_vkey,
                                xrbt_size_t xst_nsize,
                                xrbt_ctxt_t xrbt_ctxt)
{
    return xrbt_heap_alloc(xst_nsize);
}


static xrbt_void_t xrbt_comm_node_memfree(
                            x_rbnode_iter xiter_node,
                            xrbt_size_t xnode_size,
                            xrbt_ctxt_t xrbt_ctxt)
{
    xrbt_heap_free(xiter_node);
}


static xrbt_void_t xrbt_comm_vkey_copyfrom(
                            xrbt_vkey_t xrbt_dkey,
                            xrbt_vkey_t xrbt_skey,
                            xrbt_size_t xrbt_size,
                            xrbt_bool_t xbt_move ,
                            xrbt_ctxt_t xrbt_ctxt)
{
    memcpy(xrbt_dkey, xrbt_skey, xrbt_size);
}


static xrbt_void_t xrbt_comm_vkey_destruct(
                            xrbt_vkey_t xrbt_vkey,
                            xrbt_size_t xrbt_size,
                            xrbt_ctxt_t xrbt_ctxt)
{

}


static xrbt_bool_t xrbt_comm_vkey_compare(
                            xrbt_vkey_t xrbt_lkey,
                            xrbt_vkey_t xrbt_rkey,
                            xrbt_size_t xrbt_size,
                            xrbt_ctxt_t xrbt_ctxt)
{
    register xrbt_byte_t * xbt_mlptr = (xrbt_byte_t *)xrbt_lkey;
    register xrbt_byte_t * xbt_mrptr = (xrbt_byte_t *)xrbt_rkey;

    while (xrbt_size-- > 0)
    {
        if (*xbt_mlptr != *xbt_mrptr)
            return (*xbt_mlptr < *xbt_mrptr);
        xbt_mlptr += sizeof(xrbt_byte_t);
        xbt_mrptr += sizeof(xrbt_byte_t);
    }

    return XRBT_FALSE;
}



static x_rbnode_iter xrbtree_far_left(x_rbtree_ptr xthis_ptr,
                                      x_rbnode_iter xiter_node)
{
    while (XNODE_NOT_NIL(xiter_node->xiter_left))
    {
        xiter_node = xiter_node->xiter_left;
    }

    return xiter_node;
}

static x_rbnode_iter xrbtree_far_right(x_rbtree_ptr xthis_ptr,
                                       x_rbnode_iter xiter_node)
{
    while (XNODE_NOT_NIL(xiter_node->xiter_right))
    {
        xiter_node = xiter_node->xiter_right;
    }

    return xiter_node;
}

static xrbt_void_t xrbtree_dealloc(x_rbtree_ptr xthis_ptr,
                                   x_rbnode_iter xiter_node)
{
    XASSERT(XNODE_NOT_NIL(xiter_node));

    xthis_ptr->xcallback.xfunc_k_destruct(
        XNODE_VKEY(xiter_node),
        xthis_ptr->xst_ksize,
        xthis_ptr->xcallback.xctxt_t_callback);

    xthis_ptr->xcallback.xfunc_n_memfree(
        xiter_node,
        sizeof(x_rbtree_node_t) + xthis_ptr->xst_ksize,
        xthis_ptr->xcallback.xctxt_t_callback);
}


static xrbt_void_t xrbtree_clear_branch(x_rbtree_ptr xthis_ptr,
                                        x_rbnode_iter xiter_branch_root)
{
#if 1
    x_rbnode_iter xiter_node = xiter_branch_root;

    while (XNODE_NOT_NIL(xiter_node))
    {
        if (XNODE_NOT_NIL(xiter_node->xiter_right))
        {
            xrbtree_clear_branch(xthis_ptr, xiter_node->xiter_right);
        }

        xiter_branch_root = xiter_node->xiter_left;
        xrbtree_dealloc(xthis_ptr, xiter_node);
        xiter_node = xiter_branch_root;
    }
#else
    if (XNODE_IS_NIL(xiter_branch_root))
        return;

    if (XNODE_NOT_NIL(xiter_branch_root->xiter_left))
        xrbtree_clear_branch(xthis_ptr, xiter_branch_root->xiter_left);

    if (XNODE_NOT_NIL(xiter_branch_root->xiter_right))
        xrbtree_clear_branch(xthis_ptr, xiter_branch_root->xiter_right);

    xrbtree_dealloc(xthis_ptr, xiter_branch_root);
#endif
}


static x_rbnode_iter xrbtree_successor(x_rbtree_ptr xthis_ptr,
                                       x_rbnode_iter xiter_node)
{
    x_rbnode_iter xiter_parent = xiter_node->xiter_parent;

    if (XNODE_NOT_NIL(xiter_node->xiter_right))
    {
        return xrbtree_far_left(xthis_ptr, xiter_node->xiter_right);
    }

    while (XNODE_NOT_NIL(xiter_parent) &&
           (xiter_parent->xiter_right == xiter_node))
    {
        xiter_node   = xiter_parent;
        xiter_parent = xiter_parent->xiter_parent;
    }

    return xiter_parent;
}


static x_rbnode_iter xrbtree_precursor(x_rbtree_ptr xthis_ptr,
                                       x_rbnode_iter xiter_node)
{
    x_rbnode_iter xiter_parent = xiter_node->xiter_parent;

    if (XNODE_NOT_NIL(xiter_node->xiter_left))
    {
        return xrbtree_far_right(xthis_ptr, xiter_node->xiter_left);
    }

    while (XNODE_NOT_NIL(xiter_parent) &&
           (xiter_parent->xiter_left == xiter_node))
    {
        xiter_node   = xiter_parent;
        xiter_parent = xiter_parent->xiter_parent;
    }

    return xiter_parent;
}


static xrbt_void_t xrbtree_left_rotate(x_rbtree_ptr xthis_ptr,
                                       x_rbnode_iter xiter_node)
{
    x_rbnode_iter xiter_swap = xiter_node->xiter_right;

    xiter_node->xiter_right = xiter_swap->xiter_left;
    if (XNODE_NOT_NIL(xiter_swap->xiter_left))
    {
        xiter_swap->xiter_left->xiter_parent = xiter_node;
    }

    xiter_swap->xiter_parent = xiter_node->xiter_parent;
    if (XNODE_IS_NIL(xiter_node->xiter_parent))
    {
        xthis_ptr->xiter_root = xiter_swap;
    }
    else if (xiter_node == xiter_node->xiter_parent->xiter_left)
    {
        xiter_node->xiter_parent->xiter_left = xiter_swap;
    }
    else
    {
        xiter_node->xiter_parent->xiter_right = xiter_swap;
    }

    xiter_swap->xiter_left   = xiter_node;
    xiter_node->xiter_parent = xiter_swap;
}


static xrbt_void_t xrbtree_right_rotate(x_rbtree_ptr xthis_ptr,
                                        x_rbnode_iter xiter_node)
{
    x_rbnode_iter xiter_swap = xiter_node->xiter_left;

    xiter_node->xiter_left = xiter_swap->xiter_right;
    if (XNODE_NOT_NIL(xiter_swap->xiter_right))
    {
        xiter_swap->xiter_right->xiter_parent = xiter_node;
    }

    xiter_swap->xiter_parent = xiter_node->xiter_parent;
    if (XNODE_IS_NIL(xiter_node->xiter_parent))
    {
        xthis_ptr->xiter_root = xiter_swap;
    }
    else if (xiter_node == xiter_node->xiter_parent->xiter_right)
    {
        xiter_node->xiter_parent->xiter_right = xiter_swap;
    }
    else
    {
        xiter_node->xiter_parent->xiter_left = xiter_swap;
    }

    xiter_swap->xiter_right  = xiter_node;
    xiter_node->xiter_parent = xiter_swap;
}


static xrbt_void_t xrbtree_dock_fixup(x_rbtree_ptr xthis_ptr,
                                      x_rbnode_iter xiter_where)
{
    x_rbnode_iter xiter_uncle = XTREE_GET_NIL(xthis_ptr);

   
    while (X_RED == xiter_where->xiter_parent->xut_color)
    {
        if (xiter_where->xiter_parent == xiter_where->xiter_parent->xiter_parent->xiter_left)
        {
            xiter_uncle = xiter_where->xiter_parent->xiter_parent->xiter_right;
            if (X_RED == xiter_uncle->xut_color)
            {
                xiter_where->xiter_parent->xut_color = X_BLACK;
                xiter_uncle->xut_color = X_BLACK;
                xiter_where->xiter_parent->xiter_parent->xut_color = X_RED;

               
                xiter_where = xiter_where->xiter_parent->xiter_parent;
            }
            else
            {
                if (xiter_where == xiter_where->xiter_parent->xiter_right)
                {
                    xiter_where = xiter_where->xiter_parent;
                    xrbtree_left_rotate(xthis_ptr, xiter_where);
                }

                xiter_where->xiter_parent->xut_color = X_BLACK;
                xiter_where->xiter_parent->xiter_parent->xut_color = X_RED;
                xrbtree_right_rotate(xthis_ptr, xiter_where->xiter_parent->xiter_parent);
            }
        }
        else
        {
            xiter_uncle = xiter_where->xiter_parent->xiter_parent->xiter_left;
            if (X_RED == xiter_uncle->xut_color)
            {
                xiter_where->xiter_parent->xut_color = X_BLACK;
                xiter_uncle->xut_color = X_BLACK;
                xiter_where->xiter_parent->xiter_parent->xut_color = X_RED;

         
                xiter_where = xiter_where->xiter_parent->xiter_parent;
            }
            else
            {
                if (xiter_where == xiter_where->xiter_parent->xiter_left)
                {
                    xiter_where = xiter_where->xiter_parent;
                    xrbtree_right_rotate(xthis_ptr, xiter_where);
                }

                xiter_where->xiter_parent->xut_color = X_BLACK;
                xiter_where->xiter_parent->xiter_parent->xut_color = X_RED;
                xrbtree_left_rotate(xthis_ptr, xiter_where->xiter_parent->xiter_parent);
            }
        }
    }

    xthis_ptr->xiter_root->xut_color = X_BLACK;
}


static xrbt_void_t xrbtree_undock_fixup(
                                x_rbtree_ptr xthis_ptr,
                                x_rbnode_iter xiter_where,
                                x_rbnode_iter xiter_parent)
{
    x_rbnode_iter xiter_sibling = XTREE_GET_NIL(xthis_ptr);

    for (; (xiter_where != xthis_ptr->xiter_root) &&
           (X_BLACK == xiter_where->xut_color);
         xiter_parent = xiter_where->xiter_parent)
    {
        if (xiter_where == xiter_parent->xiter_left)
        {
            xiter_sibling = xiter_parent->xiter_right;
            if (X_RED == xiter_sibling->xut_color)
            {
                xiter_sibling->xut_color = X_BLACK;
                xiter_parent->xut_color = X_RED;
                xrbtree_left_rotate(xthis_ptr, xiter_parent);
                xiter_sibling = xiter_parent->xiter_right;
            }

            if (XNODE_IS_NIL(xiter_sibling))
            {
                xiter_where = xiter_parent;
            }
            else if ((X_BLACK == xiter_sibling->xiter_left->xut_color) &&
                     (X_BLACK == xiter_sibling->xiter_right->xut_color))
            {
                xiter_sibling->xut_color = X_RED;
                xiter_where = xiter_parent;
            }
            else
            {
                if (X_BLACK == xiter_sibling->xiter_right->xut_color)
                {
                    xiter_sibling->xiter_left->xut_color = X_BLACK;
                    xiter_sibling->xut_color = X_RED;
                    xrbtree_right_rotate(xthis_ptr, xiter_sibling);
                    xiter_sibling = xiter_parent->xiter_right;
                }

                xiter_sibling->xut_color = xiter_parent->xut_color;
                xiter_parent->xut_color = X_BLACK;
                xiter_sibling->xiter_right->xut_color = X_BLACK;
                xrbtree_left_rotate(xthis_ptr, xiter_parent);
                break;	
            }
        }
        else
        {
            xiter_sibling = xiter_parent->xiter_left;
            if (X_RED == xiter_sibling->xut_color)
            {
                xiter_sibling->xut_color = X_BLACK;
                xiter_parent->xut_color = X_RED;
                xrbtree_right_rotate(xthis_ptr, xiter_parent);
                xiter_sibling = xiter_parent->xiter_left;
            }

            if (XNODE_IS_NIL(xiter_sibling))
            {
                xiter_where = xiter_parent;
            }
            else if ((X_BLACK == xiter_sibling->xiter_right->xut_color) &&
                     (X_BLACK == xiter_sibling->xiter_left->xut_color))
            {
                xiter_sibling->xut_color = X_RED;
                xiter_where = xiter_parent;
            }
            else
            {
                if (X_BLACK == xiter_sibling->xiter_left->xut_color)
                {
                    xiter_sibling->xiter_right->xut_color = X_BLACK;
                    xiter_sibling->xut_color = X_RED;
                    xrbtree_left_rotate(xthis_ptr, xiter_sibling);
                    xiter_sibling = xiter_parent->xiter_left;
                }

                xiter_sibling->xut_color = xiter_parent->xut_color;
                xiter_parent->xut_color = X_BLACK;
                xiter_sibling->xiter_left->xut_color = X_BLACK;
                xrbtree_right_rotate(xthis_ptr, xiter_parent);
                break;	
            }
        }
    }

    xiter_where->xut_color = X_BLACK;
}


static xrbt_void_t xrbtree_update(x_rbtree_ptr xthis_ptr,
                                  x_rbnode_iter xiter_where,
                                  xrbt_bool_t xbt_erase)
{
    if (xbt_erase)
    {
       

        XASSERT(xthis_ptr->xst_count > 0);
        xthis_ptr->xst_count -= 1;

        if (xthis_ptr->xiter_lnode == xiter_where)
        {
            xthis_ptr->xiter_lnode =
                xrbtree_far_left(xthis_ptr, xthis_ptr->xiter_root);
        }

        if (xthis_ptr->xiter_rnode == xiter_where)
        {
            xthis_ptr->xiter_rnode =
                xrbtree_far_right(xthis_ptr, xthis_ptr->xiter_root);
        }
    }
    else
    {
       

        xthis_ptr->xst_count += 1;

        if (XNODE_IS_NIL(xthis_ptr->xiter_lnode) ||
            xthis_ptr->xcallback.xfunc_k_compare(
                                  XNODE_VKEY(xiter_where),
                                  XNODE_VKEY(xthis_ptr->xiter_lnode),
                                  xthis_ptr->xst_ksize,
                                  xthis_ptr->xcallback.xctxt_t_callback)
           )
        {
            xthis_ptr->xiter_lnode = xiter_where;
        }

        if (XNODE_IS_NIL(xthis_ptr->xiter_rnode) ||
            xthis_ptr->xcallback.xfunc_k_compare(
                                  XNODE_VKEY(xthis_ptr->xiter_rnode),
                                  XNODE_VKEY(xiter_where),
                                  xthis_ptr->xst_ksize,
                                  xthis_ptr->xcallback.xctxt_t_callback)
           )
        {
            xthis_ptr->xiter_rnode = xiter_where;
        }
    }
}


static x_rbnode_iter xrbtree_dock_pos(x_rbtree_ptr xthis_ptr,
                                      xrbt_vkey_t xrbt_vkey,
                                      xrbt_int32_t * xit_select)
{
    x_rbnode_iter xiter_where = XTREE_GET_NIL(xthis_ptr);
    x_rbnode_iter xiter_ntrav = xthis_ptr->xiter_root;
    xrbt_bool_t   xbt_to_left = XRBT_TRUE;

    while (XNODE_NOT_NIL(xiter_ntrav))
    {
        xiter_where = xiter_ntrav;

        xbt_to_left = xthis_ptr->xcallback.xfunc_k_compare(
                                     xrbt_vkey,
                                     XNODE_VKEY(xiter_ntrav),
                                     xthis_ptr->xst_ksize,
                                     xthis_ptr->xcallback.xctxt_t_callback);

        xiter_ntrav = xbt_to_left ? xiter_ntrav->xiter_left : xiter_ntrav->xiter_right;
    }

    xiter_ntrav = xiter_where;
    if (xbt_to_left)
    {
        *xit_select = -1;

        if (xiter_ntrav == XTREE_BEGIN(xthis_ptr))
            return xiter_where;
        else
            xiter_ntrav = xrbtree_precursor(xthis_ptr, xiter_ntrav);
    }
    else
    {
        *xit_select = 1;
    }

    if (xthis_ptr->xcallback.xfunc_k_compare(
                              XNODE_VKEY(xiter_ntrav),
                              xrbt_vkey,
                              xthis_ptr->xst_ksize,
                              xthis_ptr->xcallback.xctxt_t_callback))
    {
        return xiter_where;
    }

    *xit_select = 0;
    return xiter_ntrav;
}


static x_rbnode_iter xrbtree_insert_nkey(x_rbtree_ptr xthis_ptr,
                                         xrbt_vkey_t xrbt_vkey,
                                         xrbt_bool_t xbt_move,
                                         xrbt_bool_t * xbt_ok)
{
    

    x_rbnode_iter xiter_node = XTREE_GET_NIL(xthis_ptr);
    xrbt_int32_t  xit_select = -1;
    x_rbnode_iter xiter_dpos = xrbtree_dock_pos(xthis_ptr,
                                                xrbt_vkey,
                                                &xit_select);
    if (0 == xit_select)
    {
        if (XRBT_NULL != xbt_ok)
            *xbt_ok = XRBT_FALSE;
        return xiter_dpos;
    }

    

    xiter_node = (x_rbnode_iter)xthis_ptr->xcallback.xfunc_n_memalloc(
                                    xrbt_vkey,
                                    sizeof(x_rbtree_node_t) + xthis_ptr->xst_ksize,
                                    xthis_ptr->xcallback.xctxt_t_callback);
    XASSERT(XRBT_NULL != xiter_node);

    xthis_ptr->xcallback.xfunc_k_copyfrom(
                                    XNODE_VKEY(xiter_node),
                                    xrbt_vkey,
                                    xthis_ptr->xst_ksize,
                                    xbt_move,
                                    xthis_ptr->xcallback.xctxt_t_callback);

  

    xiter_node->xiter_parent = xiter_dpos;
    if (XNODE_IS_NIL(xiter_dpos))
    {
        xthis_ptr->xiter_root = xiter_node;
    }
    else if (xit_select < 0)
    {
        xiter_dpos->xiter_left = xiter_node;
    }
    else
    {
        xiter_dpos->xiter_right = xiter_node;
    }

    xiter_node->xut_color = X_RED;
    xiter_node->xut_ksize = xthis_ptr->xst_ksize;
    XTREE_SET_NIL(xthis_ptr, xiter_node->xiter_left);
    XTREE_SET_NIL(xthis_ptr, xiter_node->xiter_right);

    xrbtree_dock_fixup(xthis_ptr, xiter_node);

    

    if (XRBT_NULL != xbt_ok)
        *xbt_ok = XRBT_TRUE;
    xrbtree_update(xthis_ptr, xiter_node, XRBT_FALSE);

   

    return xiter_node;
}

xrbt_size_t xrbtree_sizeof(void)
{
    return sizeof(x_rbtree_t);
}

       - 失败，返回 XRBT_NULL；
 */
x_rbtree_ptr xrbtree_create(xrbt_size_t xst_ksize, xrbt_callback_t * xcallback)
{
    XASSERT((xst_ksize > 0) && (xst_ksize <= 0x7FFFFFFF));

    x_rbtree_ptr xthis_ptr = (x_rbtree_ptr)xrbt_heap_alloc(sizeof(x_rbtree_t));
    XASSERT(XRBT_NULL != xthis_ptr);

    return xrbtree_emplace_create(xthis_ptr, xst_ksize, xcallback);
}


xrbt_void_t xrbtree_destroy(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);

    xrbtree_emplace_destroy(xthis_ptr);
    xrbt_heap_free(xthis_ptr);
}


x_rbtree_ptr xrbtree_emplace_create(x_rbtree_ptr xthis_ptr,
                                    xrbt_size_t xst_ksize,
                                    xrbt_callback_t * xcallback)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT((xst_ksize > 0) && (xst_ksize <= 0x7FFFFFFF));

#define XFUC_CHECK_SET(xfunc, xcheck, xdef) \
    do { xfunc = (XRBT_NULL != xcheck) ? xcheck : xdef; } while (0)

    if (XRBT_NULL != xcallback)
    {
        XFUC_CHECK_SET(xthis_ptr->xcallback.xfunc_n_memalloc,
                       xcallback->xfunc_n_memalloc,
                       &xrbt_comm_node_memalloc);
        XFUC_CHECK_SET(xthis_ptr->xcallback.xfunc_n_memfree,
                       xcallback->xfunc_n_memfree,
                       &xrbt_comm_node_memfree);
        XFUC_CHECK_SET(xthis_ptr->xcallback.xfunc_k_copyfrom,
                       xcallback->xfunc_k_copyfrom,
                       &xrbt_comm_vkey_copyfrom);
        XFUC_CHECK_SET(xthis_ptr->xcallback.xfunc_k_destruct,
                       xcallback->xfunc_k_destruct,
                       &xrbt_comm_vkey_destruct);
        XFUC_CHECK_SET(xthis_ptr->xcallback.xfunc_k_compare,
                       xcallback->xfunc_k_compare,
                       &xrbt_comm_vkey_compare);

        xthis_ptr->xcallback.xctxt_t_callback = xcallback->xctxt_t_callback;
    }
    else
    {
        xthis_ptr->xcallback.xfunc_n_memalloc = &xrbt_comm_node_memalloc;
        xthis_ptr->xcallback.xfunc_n_memfree  = &xrbt_comm_node_memfree ;
        xthis_ptr->xcallback.xfunc_k_copyfrom = &xrbt_comm_vkey_copyfrom;
        xthis_ptr->xcallback.xfunc_k_destruct = &xrbt_comm_vkey_destruct;
        xthis_ptr->xcallback.xfunc_k_compare  = &xrbt_comm_vkey_compare ;
        xthis_ptr->xcallback.xctxt_t_callback = XRBT_NULL;
    }

#undef XFUC_CHECK_SET

    X_RESET_NIL(xthis_ptr);

    xthis_ptr->xst_ksize = xst_ksize;
    xthis_ptr->xst_count = 0;
    XTREE_SET_NIL(xthis_ptr, xthis_ptr->xiter_root );
    XTREE_SET_NIL(xthis_ptr, xthis_ptr->xiter_lnode);
    XTREE_SET_NIL(xthis_ptr, xthis_ptr->xiter_rnode);

    return xthis_ptr;
}


xrbt_void_t xrbtree_emplace_destroy(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    xrbtree_clear(xthis_ptr);
}


xrbt_void_t xrbtree_clear(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    xrbtree_clear_branch(xthis_ptr, xthis_ptr->xiter_root);

    X_RESET_NIL(xthis_ptr);

    xthis_ptr->xst_count = 0;
    XTREE_SET_NIL(xthis_ptr, xthis_ptr->xiter_root );
    XTREE_SET_NIL(xthis_ptr, xthis_ptr->xiter_lnode);
    XTREE_SET_NIL(xthis_ptr, xthis_ptr->xiter_rnode);
}


xrbt_size_t xrbtree_size(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return xthis_ptr->xst_count;
}


xrbt_bool_t xrbtree_empty(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return (0 == xthis_ptr->xst_count);
}


xrbt_size_t xrbtree_left_length(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);

    xrbt_size_t   xst_length = 0;
    x_rbnode_iter xiter_node = XTREE_BEGIN(xthis_ptr);

    while (xiter_node != xthis_ptr->xiter_root)
    {
        xst_length += 1;
        xiter_node = xiter_node->xiter_parent;
    }

    return xst_length;
}


xrbt_size_t xrbtree_right_length(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);

    xrbt_size_t   xst_length = 0;
    x_rbnode_iter xiter_node = XTREE_RBEGIN(xthis_ptr);

    while (xiter_node != xthis_ptr->xiter_root)
    {
        xst_length += 1;
        xiter_node = xiter_node->xiter_parent;
    }

    return xst_length;
}


x_rbnode_iter xrbtree_insert(x_rbtree_ptr xthis_ptr,
                             xrbt_vkey_t xrbt_vkey,
                             xrbt_bool_t * xbt_ok)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT(XRBT_NULL != xrbt_vkey);

    return xrbtree_insert_nkey(xthis_ptr, xrbt_vkey, XRBT_FALSE, xbt_ok);
}


x_rbnode_iter xrbtree_insert_mkey(x_rbtree_ptr xthis_ptr,
                                  xrbt_vkey_t xrbt_vkey,
                                  xrbt_bool_t * xbt_ok)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT(XRBT_NULL != xrbt_vkey);

    return xrbtree_insert_nkey(xthis_ptr, xrbt_vkey, XRBT_TRUE, xbt_ok);
}

xrbt_void_t xrbtree_erase(x_rbtree_ptr xthis_ptr, x_rbnode_iter xiter_node)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    XASSERT(xrbtree_iter_tree(xiter_node) == xthis_ptr);

    xrbtree_dealloc(xthis_ptr, xrbtree_undock(xthis_ptr, xiter_node));
}


xrbt_bool_t xrbtree_erase_vkey(x_rbtree_ptr xthis_ptr, xrbt_vkey_t xrbt_vkey)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT(XRBT_NULL != xrbt_vkey);

    x_rbnode_iter xiter_node = xrbtree_find(xthis_ptr, xrbt_vkey);
    if (XNODE_IS_NIL(xiter_node))
    {
        return XRBT_FALSE;
    }

    xrbtree_erase(xthis_ptr, xiter_node);

    return XRBT_TRUE;
}


x_rbnode_iter xrbtree_dock(x_rbtree_ptr xthis_ptr, x_rbnode_iter xiter_node)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    XASSERT(XNODE_IS_UNDOCKED(xiter_node));
    XASSERT(xiter_node->xut_ksize == xthis_ptr->xst_ksize);


    xrbt_int32_t  xit_select  = -1;
    x_rbnode_iter xiter_where = xrbtree_dock_pos(xthis_ptr,
                                                 XNODE_VKEY(xiter_node),
                                                 &xit_select);

    if (0 == xit_select)
    {
        return xiter_where;
    }


    xiter_node->xiter_parent = xiter_where;
    if (XNODE_IS_NIL(xiter_where))
    {
        xthis_ptr->xiter_root = xiter_node;
    }
    else if (xit_select < 0)
    {
        xiter_where->xiter_left = xiter_node;
    }
    else
    {
        xiter_where->xiter_right = xiter_node;
    }

    xiter_node->xut_color = X_RED;
    XTREE_SET_NIL(xthis_ptr, xiter_node->xiter_left );
    XTREE_SET_NIL(xthis_ptr, xiter_node->xiter_right);


    xrbtree_dock_fixup(xthis_ptr, xiter_node);
    xrbtree_update(xthis_ptr, xiter_node, XRBT_FALSE);


    return xiter_node;
}


x_rbnode_iter xrbtree_undock(x_rbtree_ptr xthis_ptr, x_rbnode_iter xiter_node)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    XASSERT(xrbtree_iter_tree(xiter_node) == xthis_ptr);

    x_rbnode_iter xiter_fixup  = XTREE_GET_NIL(xthis_ptr);
    x_rbnode_iter xiter_parent = XTREE_GET_NIL(xthis_ptr);
    x_rbnode_iter xiter_where  = xiter_node;
    x_rbnode_iter xiter_ntrav  = xiter_where;

    if (XNODE_IS_NIL(xiter_ntrav->xiter_left))
    {
        xiter_fixup = xiter_ntrav->xiter_right;
    }
    else if (XNODE_IS_NIL(xiter_ntrav->xiter_right))
    {
        xiter_fixup = xiter_ntrav->xiter_left;
    }
    else
    {
        xiter_ntrav = xrbtree_successor(xthis_ptr, xiter_node);
        xiter_fixup = xiter_ntrav->xiter_right;
    }

    if (xiter_ntrav == xiter_where)
    {
        xiter_parent = xiter_where->xiter_parent;
        if (XNODE_NOT_NIL(xiter_fixup))
            xiter_fixup->xiter_parent = xiter_parent;

        if (xthis_ptr->xiter_root == xiter_where)
        {
            xthis_ptr->xiter_root = xiter_fixup;
        }
        else if (xiter_parent->xiter_left == xiter_where)
        {
            xiter_parent->xiter_left = xiter_fixup;
        }
        else
        {
            xiter_parent->xiter_right = xiter_fixup;
        }
    }
    else
    {
        xiter_where->xiter_left->xiter_parent = xiter_ntrav;
        xiter_ntrav->xiter_left = xiter_where->xiter_left;

        if (xiter_ntrav == xiter_where->xiter_right)
        {
            xiter_parent = xiter_ntrav;
        }
        else
        {
            xiter_parent = xiter_ntrav->xiter_parent;
            if (XNODE_NOT_NIL(xiter_fixup))
            {
                xiter_fixup->xiter_parent = xiter_parent;
            }

            xiter_parent->xiter_left = xiter_fixup;
            xiter_ntrav->xiter_right = xiter_where->xiter_right;
            xiter_where->xiter_right->xiter_parent = xiter_ntrav;
        }

        if (xthis_ptr->xiter_root == xiter_where)
        {
            xthis_ptr->xiter_root = xiter_ntrav;
        }
        else if (xiter_where->xiter_parent->xiter_left == xiter_where)
        {
            xiter_where->xiter_parent->xiter_left = xiter_ntrav;
        }
        else
        {
            xiter_where->xiter_parent->xiter_right = xiter_ntrav;
        }

        xiter_ntrav->xiter_parent = xiter_where->xiter_parent;

        if (xiter_ntrav->xut_color != xiter_where->xut_color)
        {
            XNODE_SPIN_CLR(xiter_ntrav);
            XNODE_SPIN_CLR(xiter_where);
        }
    }

    if (X_BLACK == xiter_where->xut_color)
    {
        xrbtree_undock_fixup(xthis_ptr, xiter_fixup, xiter_parent);
    }

    xrbtree_update(xthis_ptr, xiter_where, XRBT_TRUE);

    XNODE_UNDOCK(xiter_where);

    return xiter_where;
}


x_rbnode_iter xrbtree_find(x_rbtree_ptr xthis_ptr, xrbt_vkey_t xrbt_vkey)
{
    XASSERT((XRBT_NULL != xthis_ptr) && (XRBT_NULL != xrbt_vkey));

    x_rbnode_iter xiter_node = xrbtree_lower_bound(xthis_ptr, xrbt_vkey);

    if (XNODE_IS_NIL(xiter_node) ||
        xthis_ptr->xcallback.xfunc_k_compare(
                              xrbt_vkey,
                              XNODE_VKEY(xiter_node),
                              xthis_ptr->xst_ksize,
                              xthis_ptr->xcallback.xctxt_t_callback)
       )
    {
        return XTREE_GET_NIL(xthis_ptr);
    }

    return xiter_node;
}


x_rbnode_iter xrbtree_lower_bound(x_rbtree_ptr xthis_ptr,
                                  xrbt_vkey_t xrbt_vkey)
{
    XASSERT((XRBT_NULL != xthis_ptr) && (XRBT_NULL != xrbt_vkey));

    x_rbnode_iter xiter_node = XTREE_GET_NIL(xthis_ptr);
    x_rbnode_iter xiter_trav = xthis_ptr->xiter_root;

    while (XNODE_NOT_NIL(xiter_trav))
    {
        if (xthis_ptr->xcallback.xfunc_k_compare(
                                  XNODE_VKEY(xiter_trav),
                                  xrbt_vkey,
                                  xthis_ptr->xst_ksize,
                                  xthis_ptr->xcallback.xctxt_t_callback))
        {
            xiter_trav = xiter_trav->xiter_right;
        }
        else
        {
            xiter_node = xiter_trav;
            xiter_trav = xiter_trav->xiter_left;
        }
    }

    return xiter_node;
}

x_rbnode_iter xrbtree_upper_bound(x_rbtree_ptr xthis_ptr,
                                  xrbt_vkey_t xrbt_vkey)
{
    XASSERT((XRBT_NULL != xthis_ptr) && (XRBT_NULL != xrbt_vkey));

    x_rbnode_iter xiter_node = XTREE_GET_NIL(xthis_ptr);
    x_rbnode_iter xiter_trav = xthis_ptr->xiter_root;

    while (XNODE_NOT_NIL(xiter_trav))
    {
        if (xthis_ptr->xcallback.xfunc_k_compare(
                                  xrbt_vkey,
                                  XNODE_VKEY(xiter_trav),
                                  xthis_ptr->xst_ksize,
                                  xthis_ptr->xcallback.xctxt_t_callback))
        {
            xiter_node = xiter_trav;
            xiter_trav = xiter_trav->xiter_left;
        }
        else
        {
            xiter_trav = xiter_trav->xiter_right;
        }
    }

    return xiter_node;
}


x_rbnode_iter xrbtree_root(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return xthis_ptr->xiter_root;
}


x_rbnode_iter xrbtree_begin(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return XTREE_BEGIN(xthis_ptr);
}


x_rbnode_iter xrbtree_end(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return XTREE_GET_NIL(xthis_ptr);
}


x_rbnode_iter xrbtree_next(x_rbnode_iter xiter_node)
{
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    XASSERT(XNODE_IS_DOCKED(xiter_node));
    return xrbtree_successor(XRBT_NULL, xiter_node);
}


x_rbnode_iter xrbtree_rbegin(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return XTREE_RBEGIN(xthis_ptr);
}

x_rbnode_iter xrbtree_rend(x_rbtree_ptr xthis_ptr)
{
    XASSERT(XRBT_NULL != xthis_ptr);
    return XTREE_GET_NIL(xthis_ptr);
}


x_rbnode_iter xrbtree_rnext(x_rbnode_iter xiter_node)
{
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    XASSERT(XNODE_IS_DOCKED(xiter_node));
    return xrbtree_precursor(XRBT_NULL, xiter_node);
}


xrbt_vkey_t xrbtree_iter_vkey(x_rbnode_iter xiter_node)
{
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    return XNODE_VKEY(xiter_node);
}


xrbt_bool_t xrbtree_iter_is_nil(x_rbnode_iter xiter_node)
{
    XASSERT(XRBT_NULL != xiter_node);
    return XNODE_IS_NIL(xiter_node);
}


xrbt_bool_t xrbtree_iter_is_undocked(x_rbnode_iter xiter_node)
{
    XASSERT((XRBT_NULL != xiter_node) && XNODE_NOT_NIL(xiter_node));
    return XNODE_IS_UNDOCKED(xiter_node);
}


x_rbtree_ptr xrbtree_iter_tree(x_rbnode_iter xiter_node)
{
    XASSERT((XRBT_NULL != xiter_node) && XNODE_IS_DOCKED(xiter_node));
    XASSERT(XNODE_IS_DOCKED(xiter_node));

    while (XNODE_NOT_NIL(xiter_node))
    {
        if (XNODE_IS_NIL(xiter_node->xiter_parent))
        {
            xiter_node = xiter_node->xiter_parent;
            break;
        }

        if (XNODE_IS_NIL(xiter_node->xiter_right))
        {
            xiter_node = xiter_node->xiter_right;
            break;
        }

        xiter_node = xiter_node->xiter_left;
    }

    return ((x_rbtree_nil_t *)xiter_node)->xower_ptr;
}


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif 

