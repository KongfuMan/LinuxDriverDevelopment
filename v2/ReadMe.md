This folder has the version 2 of our driver. <br>
We will use a set of functions related to register/unregister device, which will NOT require developers to 
1. select a major and minor device number in advance.
2. manually make device node 


- STEP1. Apply for (major, minor) device number from OS, if not specified; Otherwise, register the device number.
- STEP2. Add char device to the system. By this step, we don't need to manually make node under the `/dev` folder.
