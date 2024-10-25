贪吃蛇：
1. 创建一个对话框，左侧进行数据和游戏规则的展示，右侧是游戏区是picture control
2. 在对话框的 OnInitDialog() 中对游戏区进行窗口大小的设置，以及其他控件的初始化操作
3. 设计一个蛇类，成员变量有蛇的身体由vector存储CPoint点，蛇的方向由枚举量存储上下左右四个方向，成员函数
   1. Init()初始化蛇的方向和身体的各个点
   2. Draw()用于绘制蛇的身体，蛇身体的每个点由一个矩形构成，
   3. Move()移动蛇，根据蛇头的方向进行移动，计算蛇头位置，调用CheckCollision()检查是否发生碰撞，没有发生碰撞插入蛇头，调用CheckFood()检查是否吃到食物，如果吃到是否则不删除蛇尾并生成新的食物，否则删除蛇尾。
   4. SetDirection()设置蛇头的方向，不能直接掉头。
   5. GenerateFood()随机生成食物，检查食物是否在蛇身上CheckCollision()，如果在则重新生成。使用random_device随机数生成器。
   6. CheckCollision()使用any_of()结合lambda表达式，遍历蛇身体的vector判断是否和蛇发生碰撞，判断是否和边界发生碰撞。
   7. AutoDirectionChange()贪婪寻路算法，头在食物的下方，且方向不向下移动，则改变方向为上，其他三个方向同理，如果，蛇头和食物在同一条直线上且蛇背离食物移动时，在垂直方向上随机选择一个方向。算法缺点，会碰撞到自身。
   8. 重载GenerateFood()函数，考虑双人模式。
4. 对话框的成员函数
   1. OnStart()函数关联顶层菜单游戏的弹出式菜单的"开始"菜单项"，游戏开始，初始化对话框的成员变量蛇1，然后调用SetTimer()设置一个定时器，用于刷新页面，调用DrawSnakeAndFood()绘制蛇和食物。
   2. OnTimer()处理定时器消息，每个一段时间，调用蛇类的Move()，移动蛇，在移动蛇中会先判断蛇是否发生碰撞，如果发生碰撞，则Move()函数返回FALSE，杀死定时器，弹出"游戏结束提示框"。如果移动成功并且吃到食物，则更新分数和难度，然后绘制蛇和食物。
   3. DrawSnakeAndFood()调用蛇类的Draw()绘制蛇，添加绘制食物的逻辑，也是一个矩形，m_Food是对话框的成员变量
   4. PreTranslateMessage()处理键盘消息--提前翻译消息。
   5. 显示分数和难度，增加难度（提高蛇的移动速度），但有限制。
   6. 实现菜单项中的开始、暂停、继续的功能，主要是操作定时器SetTimer()、KillTimer()。
   7. 自动游戏，设置了一个布尔变量判断是否自动选择方向，如果是则调用蛇类的AutoDirectionChange()函数改变方向。
   8. 在OnTimer()中添加双人模式的逻辑判断。

问题：按键的速度超过了蛇的移动速度（更新速度），导致方向不准确
解决方法：添加一个变量存储上次变更方向的时间，限制变更频率。GetTickCount() 是 Windows API 中的一个函数，它返回系统启动以来经过的毫秒数。
bug:
1. 自动游戏的算法不能保证不碰撞自身。
2. 单人模式下的自动游戏，此时切换成双人模式游戏会崩溃。
