#导入cv模块
import cv2 as cv
#读取图像，支持 bmp、jpg、png、tiff 等常用格式
img = cv.imread("/Users/lev1s/Desktop/图像.jpeg")
#创建窗口并显示图像
cv.namedWindow("Image")
cv.imshow("Image",img)
cv.waitKey(0)
#释放窗口
cv2.destroyAllWindows()
class KC(Scene):
    def construct(self):
        KC = TextMobject("KC",color=BLUE)
        self.play(Write(KC),run_time=5)
        self.wait()
        self.play(
            KC.shift, RIGHT * 2 + UP * 2,
            rate_func=linear,
            run_time=3
            )
        self.wait()
        self.play(
            KC.shift, LEFT * 2 + UP * 2,
            rate_func=smooth,
            run_time=3
            )
        self.wait()
        self.play(
            KC.shift, RIGHT * 4 + DOWN * 2,
            rate_func=smooth,
            run_time=3
            )
        self.wait()
        self.play(
            KC.to_edge, DOWN,
            rate_func=there_and_back,
            run_time=5,
        )
        self.wait()