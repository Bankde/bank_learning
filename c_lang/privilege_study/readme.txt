This is privilege check on sticky bit (SUID)
1. check systemTouch (run by root to create password file)
2. check system "cat" to 600(root) file
3. check using cstd fread to the same file
4. check fork privilege (API getuid and geteuid)
5. check system privilege (shell, getID)
6. check exec privilege (shell, getID)
The result may be different from OS
