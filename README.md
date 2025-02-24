# Face-Recognition-based-on-FHE

这是一个用采用全同态加密技术的人脸识别认证系统。
使用说明：
1.使用系统：Linux Ubutun；

2.使用方式：在build目录中的系统终端下输入”./Program“命令运行；

3.开源库使用：请自行下载OpenCV人脸识别库，以及微软的Microsoft SEAL 全同态加密库。具体路径也需要看CMakeLists.txt文   
    件或者自己进行更改；

4.文件加密的地址设置好了，如果需要使用可以在void Mainwindow::encryptData()中的QString outPath =           
    "/home/flutter/Ciphertext/encrypted_trainer.bin";进行修改；

5.文件加密后可开启摄像头进行人脸识别，请打开摄像头；

6.文件中已上传了一张图片以及一个视频，可以进行修改；

7.运行结果可以参考Operation result reference文件，里面有运行程序时关键步骤对应的图片。

感谢您的观看。

Translation:
Here’s the translation of your content into English:

---

**This is a facial recognition authentication system utilizing Fully Homomorphic Encryption (FHE) technology.**  

**Usage Instructions:**  

1. **Supported OS**: Linux Ubuntu.  
2. **How to Run**: Navigate to the `build` directory and execute the command `./Program` in the terminal.  
3. **Required Libraries**:  
   - Manually download the **OpenCV library** for facial recognition and Microsoft's **SEAL library** for Fully Homomorphic Encryption.  
   - Adjust paths in the `CMakeLists.txt` file or modify them as needed.  
4. **File Encryption Path**:  
   - The default encryption output path is set in `void Mainwindow::encryptData()`:  
     `QString outPath = "/home/flutter/Ciphertext/encrypted_trainer.bin";`  
   - Modify this path if required.  
5. **Camera Setup**: After encrypting files, enable camera access to start facial recognition.  
6. **Sample Files**: A sample image and video are included in the system. You may replace them with your own files.  
7. **Results Reference**: See the `Operation Result Reference` document for screenshots illustrating key steps during execution.  

Thank you for your attention!  

---

Made with: Flutter
Supervisor: Dr. Sun Xiaoqiang, Shenzhen University
