
/*
*循环链表
*/

#include "list_xzy.h"
#include "string.h"

#if 1
/*
*名称：链表初始化	
*/
ENUM_LIST_XZY_ERR list_xzy_init(volatile STRUCT_LIST_XZY *p_info,unsigned char *buff,unsigned int size_buff,unsigned int unit_size,ENUM_LIST_XZY_RW_STEP flag_cover)
{
	if(p_info==NULL || buff==NULL)return enum_list_xzy_err_param_NULL;
	if(unit_size < 1)return enum_list_xzy_err_param_wrong;
	if(size_buff < unit_size)return enum_list_xzy_err_param_small;

	
	p_info->flag_on_off = enum_rw_step_idle;
	
	p_info->r.flag_on_off = enum_rw_step_idle;
	p_info->w.flag_on_off = enum_rw_step_idle;	
	
	p_info->cache_address = buff;
	p_info->cache_size = size_buff;
	p_info->cache_size_value = size_buff / unit_size * unit_size;
	p_info->unit_size = unit_size;
	p_info->flag_cover = flag_cover;
	
	p_info->flag_on_off = enum_rw_step_work;
	
	return enum_list_xzy_err_ok;
}

/*
*链表开始
*/
ENUM_LIST_XZY_ERR list_xzy_start(volatile STRUCT_LIST_XZY *p_info)
{
	if(p_info==NULL)return enum_list_xzy_err_param_NULL;
	if(p_info->flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	
	p_info->flag_on_off = enum_rw_step_idle;
	
	p_info->r.flag_on_off = enum_rw_step_idle;
	p_info->w.flag_on_off = enum_rw_step_idle;

	p_info->count_w_cover = 0;

	p_info->r.index = 0;
	p_info->r.step = enum_rw_step_idle;
	p_info->r.cir_times = 0;
	
	p_info->w.index = 0;
	p_info->w.step = enum_rw_step_idle;
	p_info->w.cir_times = 0;
	
	p_info->r.flag_on_off = enum_rw_step_work;
	p_info->w.flag_on_off = enum_rw_step_work;
	
	p_info->flag_on_off = enum_rw_step_work;
	
	return enum_list_xzy_err_ok;
}

/*
*链表结束	
*/
ENUM_LIST_XZY_ERR list_xzy_end(volatile STRUCT_LIST_XZY *p_info)
{
	if(p_info==NULL)return enum_list_xzy_err_param_NULL;
	if(p_info->flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	

	p_info->flag_on_off = enum_rw_step_idle;
	
	p_info->r.flag_on_off = enum_rw_step_idle;
	p_info->w.flag_on_off = enum_rw_step_idle;
	
	return enum_list_xzy_err_ok;
}

/*
链表读
*/
ENUM_LIST_XZY_ERR list_xzy_read(volatile STRUCT_LIST_XZY *p_info,unsigned char *p_data,unsigned int size_data,ENUM_LIST_XZY_RW_STEP flag_updata)
{
	STRUCT_LIST_XZY tmp_info = {0};
	STRUCT_LIST_XZY tmp_info_1 = {0};
	
	if(p_info==NULL)return enum_list_xzy_err_param_NULL;
	if(p_info->flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	if(p_data == NULL)return enum_list_xzy_err_param_NULL;
	if(size_data < p_info->unit_size)return enum_list_xzy_err_param_small;
		
	if(p_info->r.flag_on_off != enum_rw_step_work)return enum_list_xzy_err_read_off;
	if(p_info->r.step == enum_rw_step_work)return enum_list_xzy_err_read_busy;
	
	tmp_info = *p_info;
	p_info->r.step = enum_rw_step_work;
	if(p_info->flag_cover == enum_rw_step_work)
	{
		if(p_info->r.cir_times == p_info->w.cir_times)
			;
		else if((p_info->r.cir_times+1) == p_info->w.cir_times && \
				p_info->r.index >= p_info->w.index
			)
			;
		else
		{
			p_info->r.cir_times = p_info->w.cir_times - 1;
			p_info->r.index = p_info->w.index;
		}
	}
	if(p_info->r.cir_times == p_info->w.cir_times && \
		p_info->r.index == p_info->w.index
		)
		return enum_list_xzy_err_idle;
	memcpy(p_data,p_info->cache_address + p_info->r.index,p_info->unit_size);	
	tmp_info_1 = *p_info;
	if(p_info->flag_cover == enum_rw_step_work)
	{
		if(tmp_info.w.cir_times == tmp_info_1.w.cir_times && \
			tmp_info.w.index == tmp_info_1.w.index \
			)
			;
		if(p_info->r.index == tmp_info_1.w.index && \
			tmp_info_1.w.step == enum_rw_step_work)
		{
			return enum_list_xzy_err_recover;
		}
		else if(p_info->r.cir_times == tmp_info.w.cir_times && \
				p_info->r.index < tmp_info.w.index && \
				p_info->r.cir_times == tmp_info_1.w.cir_times && \
				p_info->r.index < tmp_info_1.w.index
				)
			
			;
		else if(p_info->r.cir_times == tmp_info.w.cir_times && \
				p_info->r.index < tmp_info.w.index && \
				(p_info->r.cir_times+1) == tmp_info_1.w.cir_times && \
				p_info->r.index >= tmp_info_1.w.index
				)
			
			;
		else if((p_info->r.cir_times+1) == tmp_info.w.cir_times && \
				p_info->r.index >= tmp_info.w.index && \
				(p_info->r.cir_times+1) == tmp_info_1.w.cir_times && \
				p_info->r.index >= tmp_info_1.w.index
				)
			
			;
		else
		{
			return enum_list_xzy_err_recover;
		}
	}
	
	if(flag_updata == enum_rw_step_work)
	{
		p_info->r.index += p_info->unit_size;
		p_info->r.cir_times += p_info->r.index / p_info->cache_size_value;
		p_info->r.index %= p_info->cache_size_value;
	}
	
	return enum_list_xzy_err_ok;
}

/*
链表缓存数据的可读次数	
*/
ENUM_LIST_XZY_ERR list_xzy_get_num(volatile STRUCT_LIST_XZY *p_info,unsigned int *item_num)
{
	STRUCT_LIST_XZY tmp_info = {0};
	
	if(p_info==NULL)return enum_list_xzy_err_param_NULL;
	if(p_info->flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	if(p_info->r.flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	if(p_info->w.flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	if(item_num==NULL)return enum_list_xzy_err_param_NULL;
	
	tmp_info = *p_info;
	if(tmp_info.r.cir_times == tmp_info.w.cir_times)
	{
		if(tmp_info.r.index == tmp_info.w.index)
			*item_num = 0;
		else
			*item_num = (tmp_info.w.index - tmp_info.r.index) / tmp_info.unit_size;
	}
	else if((tmp_info.r.cir_times+1) == tmp_info.w.cir_times)
	{
		if(tmp_info.r.index >= p_info->w.index)
			*item_num = (tmp_info.cache_size_value - (tmp_info.r.index - p_info->w.index)) / tmp_info.unit_size;
		else
			*item_num = tmp_info.cache_size_value / tmp_info.unit_size;
	}
	else
		*item_num = tmp_info.cache_size_value / tmp_info.unit_size;
		
	return enum_list_xzy_err_ok;
}

/*
链表写
*/
ENUM_LIST_XZY_ERR list_xzy_write(volatile STRUCT_LIST_XZY *p_info,unsigned char *p_data,unsigned int write_bytes)
{
	if(p_info==NULL)return enum_list_xzy_err_param_NULL;
	if(write_bytes > p_info->unit_size)return enum_list_xzy_err_param_wrong;
	if(p_info->flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	if(p_info->w.flag_on_off != enum_rw_step_work)return enum_list_xzy_err_param_wrong;
	if(p_info->w.step != enum_rw_step_work)return enum_list_xzy_err_write_busy;
	
	
	p_info->w.step = enum_rw_step_work;
	
	if(p_info->flag_cover == enum_rw_step_idle)
	{
		if((p_info->r.cir_times + 1) == p_info->w.cir_times && \
			p_info->w.index == p_info->r.index \
			)
			return enum_list_xzy_err_recover;
	}
	
	memset(p_info->cache_address + p_info->w.index,0,p_info->unit_size);
	memcpy(p_info->cache_address + p_info->w.index,p_data,write_bytes);
	
	p_info->w.index += p_info->unit_size;
	p_info->w.cir_times += p_info->w.index / p_info->cache_size_value;
	p_info->w.index %= p_info->cache_size_value;
	
	p_info->w.step = enum_rw_step_idle;
	
	return enum_list_xzy_err_ok;
}
#endif
