## Practical learning method:

Write the C version first.
Map each C variable to a register or stack slot.
Translate loop/if into labels + conditional jumps.
Compare behavior with libc on many test cases.
Debug with tiny inputs and print intermediate states.

C vs ASM mapping (mandatory functions)

## ft_strlen

C idea:

```
size_t ft_strlen(const char *s)
{
    size_t i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
```

ASM mapping:

i is in rax (starts at 0).
s is input pointer in rdi.
loop check is cmp byte [rdi + rax], 0 then je done.
increment is inc rax.

---

## ft_strcmp

C idea:

```
int ft_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

ASM mapping:

index i often in rcx.
load bytes with mov al, [rdi + rcx] and mov dl, [rsi + rcx].
if different: zero-extend bytes (movzx) and subtract.
if same and zero byte reached: return 0.

test al, al -> check if al = \0. No need to check dl because we cmp al and dl just before

---

## ft_write

C idea:

```
ssize_t ft_write(int fd, const void *buf, size_t count)
{
    ssize_t ret = write(fd, buf, count);
    if (ret < 0)
        return -1;
    return ret;
}
```

ASM mapping (Linux):

syscall number for write goes in rax **(1)**.  
args are already in rdi (fd), rsi (buf), rdx (count).  
syscall executes kernel call.  
if rax < 0, error path:  
neg rax to get positive errno  
get errno pointer via __errno_location  
store errno code there  
return -1 in rax.

---

## ft_read

C idea:

```
ssize_t ft_read(int fd, void *buf, size_t count)
{
    ssize_t ret = read(fd, buf, count);
    if (ret < 0)
        return -1;
    return ret;
}
```

ASM mapping (Linux):

syscall number for read in rax **(0)**.  
same arg registers as C ABI.  
same error pattern as ft_write: if rax < 0 then set errno and return -1.

---

## ft_strcpy

C idea:

```
char *ft_strcpy(char *dst, const char *src)
{
    char *ret = dst;

    while (*src)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return ret;
}
```

ASM mapping:

dst is in rdi, src is in rsi. mov rax, rdi saves the original dst pointer (return value). loop copies one byte: mov dl, [rsi] then mov [rdi], dl. (On x86-64, `mov` cannot copy memory → memory in one instruction)  
inc rsi / inc rdi advances both pointers. test dl, dl + jne .loop continues until the '\0' byte was copied. ret returns rax (original dst).

---

## ft_strdup

C idea:

```
char *ft_strdup(const char *s1)
{
    size_t len_plus_null;
    char *dst;

    len_plus_null = ft_strlen(s1) + 1;
    dst = malloc(len_plus_null);
    if (dst == NULL)
        return NULL;
    ft_strcpy(dst, s1);
    return dst;
}
```

ASM mapping:

s1 arrives in rdi.
push rdi saves s1 (needed later; rdi will be reused).
call ft_strlen then inc rax -> strlen(s1) + 1 (space for '\0').
mov rdi, rax + call malloc allocates the new buffer.
test rax, rax + je .malloc_failed -> if malloc failed, return NULL.
mov rdi, rax (dst), mov rsi, [rsp] (saved s1), call ft_strcpy.
add rsp, 8 cleans the saved s1 from the stack.
ret returns rax (pointer from strcpy, which is dst).

Important: push rdi before calls because caller-saved registers can be overwritten.

---

C vs ASM mapping (bonus functions)

t_list layout reminder:

```
typedef struct s_list
{
    void *data;          // offset 0
    struct s_list *next; // offset 8
} t_list;                // size 16
```

---

## ft_atoi_base

C idea:

```
int ft_atoi_base(char *str, char *base)
{
    // 1) validate base (len >= 2, no +, -, whitespace, no duplicates)
    // 2) skip whitespace in str
    // 3) handle + / - signs
    // 4) convert digits while chars are in base
    // 5) apply sign and return
}
```

ASM mapping:

str in rdi, base in rsi, return in eax.
r8 = base length.
r9 walks through str.
r10 = sign (1 or -1).
eax = result.
rcx = digit index in base.

Validate base first; if invalid -> return 0.
Skip spaces/whitespace (32 and 9..13).
For each '-' flip sign (neg r10d).
Convert: result = result * base_len + digit_index
(imul eax, r8d then add eax, ecx).
If sign was negative, neg eax before return.

---

## ft_list_push_front

C idea:

```
void ft_list_push_front(t_list **begin_list, void *data)
{
    t_list *new_node;

    if (!begin_list)
        return;
    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = *begin_list;
    *begin_list = new_node;
}
```

ASM mapping:

begin_list in rdi, data in rsi.
Save both on stack before call malloc (caller-saved regs).
malloc(16) for one node.
new_node->data = [rax + 0]
new_node->next = *begin_list ([rax + 8])
*begin_list = new_node

---

## ft_list_size

C idea:

```
int ft_list_size(t_list *begin_list)
{
    int count = 0;

    while (begin_list)
    {
        count++;
        begin_list = begin_list->next;
    }
    return count;
}
```

ASM mapping:

eax = counter (starts at 0).
rdi = current node.
loop: if rdi == 0 return.
inc eax, then rdi = [rdi + 8] (next), jump loop.

---

## ft_list_sort

C idea (bubble sort by swapping data):

```
void ft_list_sort(t_list **begin_list, int (*cmp)())
{
    int swapped;
    t_list *a;
    t_list *b;
    void *tmp;

    if (!begin_list || !cmp || !*begin_list)
        return;
    do {
        swapped = 0;
        a = *begin_list;
        while (a && a->next)
        {
            b = a->next;
            if (cmp(a->data, b->data) > 0)
            {
                tmp = a->data;
                a->data = b->data;
                b->data = tmp;
                swapped = 1;
            }
            a = b;
        }
    } while (swapped);
}
```

ASM mapping:

rbx = begin_list (must survive calls).
r12 = cmp function pointer.
r13 = swapped flag.
rdx = current node a, rcx = next node b.

Inner loop compares adjacent nodes with call r12.
If cmp > 0, swap data pointers and set swapped = 1.
Continue the pass after each swap.
Only after a full pass: if swapped != 0, restart from *begin_list.

Important: keep begin_list in rbx, not only in rdi (call clobbers rdi).

---

## ft_list_remove_if

C idea:

```
void ft_list_remove_if(t_list **begin_list, void *data_ref,
                       int (*cmp)(), void (*free_fct)(void *))
{
    t_list **curr;
    t_list *node;

    if (!begin_list || !cmp || !free_fct)
        return;
    curr = begin_list;
    while (*curr)
    {
        node = *curr;
        if (cmp(node->data, data_ref) == 0)
        {
            *curr = node->next;
            free_fct(node->data);
            free(node);
        }
        else
            curr = &node->next;
    }
}
```

ASM mapping:

r12 = data_ref
r13 = cmp
r14 = free_fct
r15 = curr (t_list **), pointer to the pointer holding current node
[rsp] = temporary current node

Loop:
node = *r15
call cmp(node->data, data_ref)
if equal: free_fct(data), *curr = next, free(node), stay on same r15
if not equal: r15 = &node->next (lea r15, [r9 + 8])

Key idea: r15 is not the node, it is the link pointer (t_list **).
That makes removing head and middle nodes the same.

---

Mental model for conditions and variables

C variable -> register/stack memory.
C if -> cmp/test + jump (je, jne, jl, ...).
C while -> loop label + condition jump back to loop.
C return x -> put x in rax then ret.

Function calls may overwrite caller-saved registers, so preserve what you need.