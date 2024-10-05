// Copyright (c) 2024 ACM Class, SJTU

namespace sjtu
{

class BuddyAllocator
{
public:
    /**
     * @brief Construct a new Buddy Allocator object with the given RAM size and
     * minimum block size.
     *
     * @param ram_size Size of the RAM. The address space is 0 ~ ram_size - 1.
     * @param min_block_size Minimum size of a block. The block size is 2^k where
     * k >= min_block_size.
     */
    BuddyAllocator(int ram_size, int min_block_size):ram_size(ram_size),min_block_size(min_block_size)
    {
        // TODO(student): Implement this function.
        block_cnt=ram_size/min_block_size;
        capacity=new int[2*block_cnt];
        int cap=block_cnt;
        int next_layer=2;
        for(int i=1;i<2*block_cnt;i++)
        {
            if(i==next_layer)
            {
                next_layer*=2;
                cap/=2;
            }
            capacity[i]=cap;
        }
    }

    ~BuddyAllocator()
    {
        delete[] capacity;
    }

    
    int malloc_aux(int now,int range_size,int range_s,int malloc_size)
    {
        if(range_size==malloc_size)
        {
            capacity[now]=0;
            return range_s;
        }
        int lson=now*2;
        int rson=lson+1;
        int half_range_size=range_size/2;
        int ret;

        //pushdown
        //none

        //dfs
        if(capacity[lson]>=malloc_size)
            ret=malloc_aux(lson,half_range_size,range_s,malloc_size);
        else
            ret=malloc_aux(rson,half_range_size,range_s+half_range_size,malloc_size);

        //pushup
        if(lson==range_size/2&&rson==range_size/2)
            capacity[now]=range_size;
        else
            capacity[now]=std::max(capacity[rson],capacity[lson]);

        
        return ret;
    }


    /**
     * @brief Allocate a block with the given size at the minimum available
     * address.
     *
     * @param size The size of the block.
     * @return int The address of the block. Return -1 if the block cannot be
     * allocated.
     */
    int malloc(int size)
    {
        // TODO(student): Implement this function.
        size=size/min_block_size;
        if(size==block_cnt)return -1;
        if(capacity[1]<size)return -1;
        return malloc_aux(1,block_cnt,0,size)*min_block_size;
    }

    int malloc_at_aux(int now,int range_size,int range_s,int malloc_size,int malloc_s)
    {
        if(range_size<malloc_size)
            return -1;
        if(range_size==malloc_size)
        {
            capacity[now]=0;
            return range_s;
        }
        int lson=now*2;
        int rson=lson+1;
        int half_range_size=range_size/2;
        int ret=-1;

        //pushdown
        //none

        //dfs
        if(malloc_s<range_s+half_range_size)
        {
            if(capacity[lson]>=malloc_size)
                ret=malloc_at_aux(lson,half_range_size,range_s,malloc_size,malloc_s);
        }
        else
        {
            if(capacity[rson]>=malloc_size)
                ret=malloc_at_aux(rson,half_range_size,range_s+half_range_size,malloc_size,malloc_s);
        }

        //pushup
        if(capacity[lson]==half_range_size&&capacity[rson]==half_range_size)
            capacity[now]=range_size;
        else
            capacity[now]=std::max(capacity[rson],capacity[lson]);

        
        return ret;
    }

    /**
     * @brief Allocate a block with the given size at the given address.
     *
     * @param addr The address of the block.
     * @param size The size of the block.
     * @return int The address of the block. Return -1 if the block cannot be
     * allocated.
     */
    int malloc_at(int addr, int size)
    {
        // TODO(student): Implement this function.
        addr/=min_block_size;
        size/=min_block_size;
        if(size==block_cnt)return -1;
        // if((addr&-addr)!=size)return -1;
        
        int ret=malloc_at_aux(1,block_cnt,0,size,addr);
        if(ret==-1)return -1;
        else return ret*min_block_size;
    }

    void free_at_aux(int now,int range_size,int range_s,int malloc_size,int malloc_s)
    {
        if(range_size<malloc_size)
            return;
        if(range_size==malloc_size)
        {
            capacity[now]=range_size;
            return;
        }
        int lson=now*2;
        int rson=lson+1;
        int half_range_size=range_size/2;

        //pushdown
        //none

        //dfs
        if(malloc_s<range_s+half_range_size)
            free_at_aux(lson,half_range_size,range_s,malloc_size,malloc_s);
        else
            free_at_aux(rson,half_range_size,range_s+half_range_size,malloc_size,malloc_s);
        

        //pushup
        if(capacity[lson]==half_range_size&&capacity[rson]==half_range_size)
            capacity[now]=range_size;
        else
            capacity[now]=std::max(capacity[rson],capacity[lson]);
        
    }


    /**
     * @brief Deallocate a block with the given size at the given address.
     *
     * @param addr The address of the block. It is ensured that the block is
     * allocated before.
     * @param size The size of the block.
     */
    void free_at(int addr, int size)
    {
        // TODO(student): Implement this function.
        addr/=min_block_size;
        size/=min_block_size;
        
        free_at_aux(1,block_cnt,0,size,addr);
    }

private:
    // Add whatever you need here.
    int ram_size;
    int min_block_size;
    int block_cnt;
    int *capacity;
};

} // namespace sjtu