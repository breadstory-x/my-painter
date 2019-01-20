# my paint
## 系统介绍
 - 该软件采用Qt5.9.6编写，能实现简易的画图功能，FinalNew中为最新版本。具体功能如下：
	 - 二维图元的绘制：直线、圆、椭圆、矩形、多边形、填充
	 - 直线的裁剪功能，支持单直线裁剪
	 - 二维图元的编辑：可通过拖动控制点来改变图形的形状，能对刚画的图形进行编辑
	 - 二维图元的变换：平移、旋转、缩放。能对刚画的图形进行变换
	 - 二维图像的保存功能：支持保存成jpg、bmp格式
	 - 三维图形的显示：能加载OFF格式的三维图形，有面模型和线模型两种呈现方式，并能改变观察的视角。
## 使用说明
### 二维图元的绘制与编辑
	颜色限定为黑色，画笔宽度限定为3点，不可修改。
#### 直线、圆、椭圆、矩形的绘制
 选中相应图标，单击鼠标左键，拖动至合适位置释放即可。
#### 多边形的绘制
 选中多边形图标，单击鼠标左键并拖动，绘制多边形的第一条边，再次单击单击鼠标左键并拖动，绘制多边形的第二条边，以此类推。当绘制完成时，单击鼠标右键即可封口。
#### 曲线的绘制
 与多边形类似，选中曲线图标，单击鼠标左键并拖动，绘制曲线的第一条辅助边，以同样的方法画三条辅助边后自动生成曲线。
#### 图形的编辑
 图形绘制完成后，可看到蓝色边框白色实心圆，他们是图形的控制点，鼠标移上去指针会变成十字形。鼠标左键拖动即可改变控制点的位置，完成编辑。
 **控制点说明**：
 - 直线为两端点，圆为左上、右下两点，椭圆、矩形为左上、左下、右上、右下四点，多边形为各个端点，曲线为如图所示四点
#### 图形的填充
 选择填充按钮，可激活颜色设置图标，点击可修改颜料桶的颜色，默认为黑色。之后鼠标左键单击画布任意位置即可完成填充。
### 二维图形的变换
1. 平移
 - 平移控制点为图形中心的天蓝色实心点，鼠标左键点击并拖动即可改变图形位置。
2. 旋转
 - 旋转控制点为橙色实心点，鼠标左键点击并拖动即可使图形旋转
```
**注意**
（1）圆无法旋转，因为圆旋转后跟之前保持一致，没有必要，因此也没有旋转控制点。
（2）旋转之后无法继续编辑，因此编辑控制点会消失，但可继续平移和缩放，也可继续旋转。
（3）均绕中心点旋转。	
```
3. 缩放
 - 绘制完图形后，点击工具栏的放大、缩小图标即可按完成缩放。缩放的中心为各图形的中心点。
 - 缩放比例：放大：1.25；缩小：0.8
### 直线的裁剪
 - 裁剪可支持对刚画完的直线裁剪。
 - 选择选择框图标，可激活裁剪按钮。裁剪框画法与矩形相同，画完后可拖动左上、右下两个控制点进行编辑。确定好裁剪范围后，点击裁剪按钮，即可完成直线的裁剪。
### 画布清空与图像保存
1. 画布清空
 - 点击工具栏的清空图标即可。
2. 图像保存
 - 点击工具栏的保存图标，在弹出的对话框中选择保存路径，填好文件名即可。支持保存为jpg、bmp格式。
### 三维模型的显示
1. 点击打开图标，选择合适的OFF文件即可。
2. 操作说明：
	 - 键盘
		 - 数字1：放大
		 - 数字2：缩小
		 - 方向键上、下：按x轴旋转
		 - 方向键左、右：按y轴旋转
		 - 字母Z、X：按z轴旋转
		 - 字母L：在面模型和线框架之间切换
		 - F1：全屏显示
		 - Esc：关闭窗口
	- 鼠标
		- 单击鼠标左键并拖动，可使图形旋转。
		- 鼠标滑轮可改变视角远近。





