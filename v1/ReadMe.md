This the 1st version.
`chrdevchild.c` implements the minimum driver 
code to make it run.

- Compile module (v1):
    - Open terminal and `cd {project_root}/v1/`
    - Run `make build`
- Run module (v1):
    - Open terminal
    - Run `sudo -i` and input password
    - `cd /lib/modules/$(uname -r)/`
    - `./chrdevbaseAPP /dev/chrdevchild 1`

