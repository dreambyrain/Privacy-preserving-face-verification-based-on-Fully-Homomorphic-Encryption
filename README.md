# Face-Recognition-based-on-FHE

这是一个用采用全同态加密技术的人脸识别认证系统。

使用说明：
1.使用系统：Linux Ubuntu；

2.使用方式：在build目录中的系统终端下输入”./Program“命令运行；

3.开源库使用：请自行下载OpenCV人脸识别库，以及微软的Microsoft SEAL 全同态加密库。具体路径也需要看CMakeLists.txt文   
    件己进行更改；

4.文件加密的地址需要在void Mainwindow::encryptData()中的QString outPath =           
    "/home/   /Ciphertext/encrypted_trainer.bin";进行修改；

5.运行结果可以参考Operation result reference文件，里面有运行程序时关键步骤对应的图片。

6.需要根据自己的路径更改CMakeLists.txt文件中的SEAL库等路径。

感谢您的观看。

Translation:
Here's the translation of your instructions:

---

**Instructions:**

1. **System Requirements:** Linux Ubuntu.

2. **How to Use:** In the terminal under the `build` directory, enter the command `./Program` to run.

3. **Open Source Libraries:** Please download the OpenCV face recognition library and Microsoft's Microsoft SEAL fully homomorphic encryption library yourself. Specific paths should be modified in the `CMakeLists.txt` file accordingly.

4. **File Encryption Path:** The encryption path for files needs to be modified in `void Mainwindow::encryptData()` in the line `QString outPath = "/home/   /Ciphertext/encrypted_trainer.bin";`.

5. **Reference for Operation Results:** The "Operation result reference" file can be referred to, where images corresponding to key steps during the program execution are provided.

6. **Path Modifications:** Make sure to modify the paths for the SEAL library and others in the `CMakeLists.txt` file according to your system setup.

---

**Thank you for your attention.**

---


Made with: Flutter
Supervisor: Dr. Sun Xiaoqiang, Shenzhen University
