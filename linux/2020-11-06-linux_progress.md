
[index](./index.md)

# Life and Death of a Linux Process

---

Author:sandylaw 

Email :freelxs@gmail.com

Date  :2020-11-06

tags  :linux 

---

This post contains a rough sketch of the life and death of a process on Linux. It is a first-order approximation only. A later post will refine this further and provide a more precise description, adding details about pid namespaces, obscure syscalls, and little known flags.
## Birth

Every time a process is created, really another process split itself using the fork or clone syscall. After forking, processes usually run the execve syscall to swap the currently executing binary with another one. For example, when you run ls from a bash shell then first bash splits itself into two bash processes using fork and then the child bash shell uses exec to change itself into ls. The child dies when ls finishes executing leaving only the original bash process.

In practice, programs almost never call the syscalls directly - they use libc wrappers instead or a libc function like system which under the hood uses fork and execve (or one of several execve variants).

## Death

How do processes die? They almost always call the exit or exit_group syscalls. If the programmer doesn’t explicitly call exit and instead returns from main then exit is called anyway because the compiler wrapped main with a libc main that calls exit for you. If the program was compiled without libc and the programmer doesn’t call exit explicitly then returning from main will cause a segfault or another critical signal because return will try to pop an illegal return address from the stack. This brings us to the second-to-last way that processes can die which is via signals like SIGTERM or SIGKILL. Finally, the last way for a process to die is to pull the plug on your computer.

## Identity and Zombiehood

Every process has a unique pid - or at least it is unique until the kernel recycles the pid sometime after the process dies. Before a process’ pid can be recycled, the parent process should call wait, waitpid, or waitid on the child. (In the example presented earlier, bash needs to call wait on ls.) If the parent doesn’t wait on the child then the child process becomes a zombie which means it hangs around in the kernel’s process table wasting resources. If the parent itself dies then the process gets re-assigned a parent with pid one - that is, the pid of the unique init process which automatically calls wait and frees up the process.

## Threads - Lesser Processes

What is a thread, really? On Linux, threads are more or less independent processes which happen to share the same memory and some other resources. They are created by calling clone with the appropriate flag(s). In kernel terminology, every thread has it’s own unique pid and all threads in the same process share the same tgid (thread group id) which is equal to first thread’s pid. So from the kernel’s perspective really pids identify threads, tgids identify processes, and the pid is equal to the tgid for single-thread processes. What makes this confusing is that the terminology in usermode is different as you can see in the following table:
Kernel name (in task_struct)    Usermode name   Returned by syscall
tgid (thread group id)  pid (process id)    getpid
pid (process id)    tid (thread id)     gettid, clone, fork

## Closing Notes

This was an overview of processes on Linux. I’ve written a lot about Linux processes lately. If you liked this post, you should read my other posts - especially my most popular post on the difficulties of tracking running processes on Linux. I also write about other Linux topics, like the most common bug that developers encounter when using BPF.

This blog doesn’t support comments, but I want to hear from you. I prefer a more personal one-to-one connection than you typically find in comment sections. Feel free to contact me on LinkedIn and send me your thoughts on this post.

Link:
- https://natanyellin.com/posts/life-and-death-of-a-linux-process/
