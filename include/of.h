#ifndef __OF_H
#define __OF_H

#include <fdt.h>
#include <errno.h>
#include <asm/byteorder.h>

int fdt_print(struct fdt_header *working_fdt, const char *pathp);

struct fdt_header *of_get_fixed_tree(struct fdt_header *fdt);
int of_fix_tree(struct fdt_header *fdt);
int of_register_fixup(int (*fixup)(struct fdt_header *));

int fdt_find_and_setprop(struct fdt_header *fdt, const char *node, const char *prop,
			 const void *val, int len, int create);
void do_fixup_by_path(struct fdt_header *fdt, const char *path, const char *prop,
		      const void *val, int len, int create);
void do_fixup_by_path_u32(struct fdt_header *fdt, const char *path, const char *prop,
			  u32 val, int create);
int fdt_get_path_or_create(struct fdt_header *fdt, const char *path);

#define OF_BAD_ADDR      ((u64)-1)

typedef u32 phandle;

struct property {
	char *name;
	int length;
	void *value;
	struct list_head list;
};

struct device_node {
	char *name;
	char *full_name;

	struct list_head properties;
	struct device_node *parent;
	struct list_head children;
	struct list_head parent_list;
	struct list_head list;
	struct resource *resource;
	struct device_d *device;
	struct list_head phandles;
	phandle phandle;
};

struct of_device_id {
	char *compatible;
	unsigned long data;
};

struct driver_d;

int of_match(struct device_d *dev, struct driver_d *drv);

struct property *of_find_property(const struct device_node *node, const char *name);

struct device_node *of_find_node_by_path(const char *path);

struct fdt_header *fdt_get_tree(void);

#define device_node_for_nach_child(node, child) \
	list_for_each_entry(child, &node->children, parent_list)

/* Helper to read a big number; size is in cells (not bytes) */
static inline u64 of_read_number(const __be32 *cell, int size)
{
	u64 r = 0;
	while (size--)
		r = (r << 32) | be32_to_cpu(*(cell++));
	return r;
}

int of_property_read_u32_array(const struct device_node *np,
			       const char *propname, u32 *out_values,
			       size_t sz);

static inline int of_property_read_u32(const struct device_node *np,
				       const char *propname,
				       u32 *out_value)
{
	return of_property_read_u32_array(np, propname, out_value, 1);
}

const void *of_get_property(const struct device_node *np, const char *name,
			 int *lenp);

int of_parse_phandles_with_args(struct device_node *np, const char *list_name,
				const char *cells_name, int index,
				struct device_node **out_node,
				const void **out_args);

int of_get_named_gpio(struct device_node *np,
                                   const char *propname, int index);

struct device_node *of_find_node_by_phandle(phandle phandle);
void of_print_property(const void *data, int len);

int of_machine_is_compatible(const char *compat);

#define OF_ROOT_NODE_SIZE_CELLS_DEFAULT 1
#define OF_ROOT_NODE_ADDR_CELLS_DEFAULT 1

void of_print_nodes(struct device_node *node, int indent);
int of_probe(void);
int of_parse_dtb(struct fdt_header *fdt);
void of_free(struct device_node *node);
int of_unflatten_dtb(struct fdt_header *fdt);
struct device_node *of_new_node(struct device_node *parent, const char *name);
struct property *of_new_property(struct device_node *node, const char *name,
		const void *data, int len);
void of_delete_property(struct property *pp);

int of_property_read_string(struct device_node *np, const char *propname,
				const char **out_string);

#ifdef CONFIG_OFDEVICE
int of_parse_partitions(const char *cdevname,
			    struct device_node *node);

struct device_node *of_get_root_node(void);
int of_alias_get_id(struct device_node *np, const char *stem);
int of_device_is_stdout_path(struct device_d *dev);
const char *of_get_model(void);
void *of_flatten_dtb(void);
#else
static inline int of_parse_partitions(const char *cdevname,
					  struct device_node *node)
{
	return -EINVAL;
}

static inline struct device_node *of_get_root_node(void)
{
	return NULL;
}

static inline int of_alias_get_id(struct device_node *np, const char *stem)
{
	return -ENOENT;
}

static inline int of_device_is_stdout_path(struct device_d *dev)
{
	return 0;
}

static inline const char *of_get_model(void)
{
	return NULL;
}

static inline void *of_flatten_dtb(void)
{
	return NULL;
}
#endif

#endif /* __OF_H */
