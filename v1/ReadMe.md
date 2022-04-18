This the 1st version.
`chrdevchild.c` implements the minimum driver 
code to make it run.

Compile module (v1):
- Open terminal and `cd` into the root of the project
- Run `make --makefile=./v1.Makefile`

Run module (v1):
- Open terminal
- Run `sudo -i` and input password
- `cd /lib/modules/$(uname -r)/`
- `./chrdevbaseAPP /dev/chrdevchild 1`

