#include"my_info.h"

MODULE_LICENSE("GPL");

static int my_info_proc_show_v_c(struct seq_file *m, void *v);
static int my_info_proc_show_m_t(struct seq_file *m, void *v);

static int my_info_proc_show_v_c(struct seq_file *m, void *v)
{
    //struct cpuinfo_x86 *cpu;
    //cpu = v;

    seq_printf(m, "========Version======== \n");
    seq_printf(m, "Linux version %s \n", UTS_RELEASE);
    seq_printf(m, "========CPU============ \n");
    //seq_printf(m, "processor   : %u \n", cpu -> cpu_index);
    return my_info_proc_show_m_t(m, v);
}

static int my_info_proc_show_m_t(struct seq_file *m, void *v)
{
    struct sysinfo sys;
    struct timespec64 time;
    unsigned long pages[NR_LRU_LISTS];
    unsigned long dirty, kernel, writeback, pagetable;
    int lru;

    for(lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
        pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

#define K(x) ((x) << (PAGE_SHIFT - 10))
    si_meminfo(&sys);
    get_monotonic_boottime64(&time);
    dirty = global_node_page_state(NR_FILE_DIRTY);
    writeback = global_node_page_state(NR_WRITEBACK);
    kernel = global_zone_page_state(NR_KERNEL_STACK_KB);
    pagetable = global_zone_page_state(NR_PAGETABLE);
    seq_printf(m, "========Memory========= \n");
    seq_printf(m, "Memtotal    : %8lu kB\n", K(sys.totalram));
    seq_printf(m, "Memfree     : %8lu kB\n", K(sys.freeram));
    seq_printf(m, "Buffers     : %8lu kB\n", K(sys.bufferram));
    seq_printf(m, "Active      : %8lu kB\n", K((pages[LRU_ACTIVE_ANON] + pages[LRU_ACTIVE_FILE])));
    seq_printf(m, "Inactive    : %8lu kB\n", K((pages[LRU_INACTIVE_ANON] + pages[LRU_INACTIVE_FILE])));
    seq_printf(m, "Shmem       : %8lu kB\n", K(sys.sharedram));
    seq_printf(m, "Dirty       : %8lu kB\n", K(dirty));
    seq_printf(m, "Writeback   : %8lu kB\n", K(writeback));
    seq_printf(m, "Kernalstack : %8lu kB\n", kernel);
    seq_printf(m, "Pagetable   : %8lu kB\n", K(pagetable));
    seq_printf(m, "========Time=========== \n");
    seq_printf(m, "uptime      : %ld \n", time.tv_sec);
    return 0;
}

static int my_info_proc_open(struct inode *inode, struct file *file)
{
    return single_open(file, my_info_proc_show_v_c, NULL);
}

static const struct file_operations my_info_proc_fops =
{
    .owner = THIS_MODULE,
    .open = my_info_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

static int __init my_info_proc_init(void)
{
    proc_create("my_info", 0, NULL, &my_info_proc_fops);
    return 0;
}

static void __exit my_info_proc_exit(void)
{
    remove_proc_entry("my_info", NULL);
}

module_init(my_info_proc_init);
module_exit(my_info_proc_exit);
