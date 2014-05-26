- Author: Hongxing Yuan (yuanhx@mail.ustc.edu.cn)
- Version: 1.0 (last update: May-21-2014)

- Note:
(1) The implementation is for our submitted paper:
    Nonlocal Random Walks Algorithm for Semi-Automatic 2D-to-3D Image Conversion
(2) This software is used to generate user labels, masks for semi-automatic 2D-to-3D conversion.
(3) We use OpenCV 2.4.6 to read and write images, the higher version should also work.
(4) This code has been tested in Microsoft Visual Studio 2012 running on Windows 7(64bit). 
    
- Usage example:
    brush2depth girl\girl.png
(1) Press 'esc' key to quit
(2) Press 'r' key to reset user input
(3) Press 'w' key to generate user labels, there will be 3 images,
    which are 'imglbls.png', 'mask.png' and 'strokes.png'.
    
- For any questions, suggestions or bug reports, please, contact yuanhx@mail.ustc.edu.cn
