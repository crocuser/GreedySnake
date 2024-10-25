#include "pch.h"
#include "Snake.h"

Snake::Snake()
{
}

Snake::~Snake()
{
}

void Snake::Init(int row)
{
    m_Direction = RIGHT;
    m_bGrow=FALSE;
    //先有蛇，后有食物
    m_vBody.clear();
    m_vBody.push_back(CPoint(10, row));
    m_vBody.push_back(CPoint(9, row));
    m_vBody.push_back(CPoint(8, row));

    m_LastDirectionChangeTime =::GetTickCount();
}

BOOL Snake::Move(CPoint food)
{
    //获取蛇头的方向--问题：按键的速度超过了蛇的移动速度，导致蛇头方向不准确
    int headX=m_vBody[0].x;
    int headY=m_vBody[0].y;
    switch (m_Direction)
    {
    case UP:
        headY--;
        m_Direction = UP;
        break;
    case DOWN:
        headY++;
        m_Direction = DOWN;
        break;
    case LEFT:
        headX--;
        m_Direction = LEFT;
        break;
    case RIGHT:
        headX++;
        m_Direction = RIGHT;
        break;
    }
    //检查蛇头是否碰撞
    if (CheckCollision(headX, headY))
    {
        return FALSE;
    }
    //插入蛇头
    m_vBody.insert(m_vBody.begin(), CPoint(headX, headY));//头部插入到队列头
    //检查是否吃到食物
    if (CheckFood(food))
    {
        //吃到食物
        m_bGrow = TRUE;
    }
    else
    {
        //删除尾部
        m_vBody.pop_back();
        m_bGrow = FALSE;
    }
    return TRUE;
}

BOOL Snake::CheckCollision(int x,int y) const
{
    //TODO: 增加蛇身的碰撞检测
    BOOL collision= FALSE;
    // C++ 的标准库算法 any_of，其功能是检查给定范围内是否有任何元素满足特定条件。
    //any_of 是一个算法，它接受一对迭代器和一个谓词（条件），如果在迭代范围内找到至少一个元素使得谓词返回 true，则 any_of 返回 true；否则返回 false。
    //lambda表达式的语法如下：[x,y]捕获列表，（CPoint p）参数列表，表示当前正在遍历的元素，返回值是布尔值。
    if (any_of(m_vBody.begin(), m_vBody.end(), [x, y](CPoint p) { return p.x == x && p.y == y; }))
    {
        collision = TRUE;
    }
    //蛇是否碰到边界
    if (x < 0 || x >= GAMEAREA_WIDTH / SNAKE_BODYSIZE || y < 0 || y >= GAMEAREA_HEIGHT / SNAKE_BODYSIZE)
    {
        collision = TRUE;
    }
    return collision;
}

BOOL Snake::CheckFood(CPoint food)
{
    //TODO: 增加食物的检测
    return (m_vBody[0].x == food.x && m_vBody[0].y == food.y);
}

void Snake::SetDirection(Direction dir)
{
    //TODO: 增加方向的限制--不能掉头
    if ((dir == UP && m_Direction != DOWN)
        || (dir == DOWN && m_Direction != UP)
        || (dir == LEFT && m_Direction != RIGHT)
        || (dir == RIGHT && m_Direction != LEFT))
    {
        m_Direction = dir;
    }
}

BOOL Snake::IsGrow()
{
    return m_bGrow;
}

void Snake::Draw(CDC* pDC, COLORREF color)
{
    CBrush brush(color);
    int left, top, right, bottom;
    //TODO: 增加蛇身的绘制
    for (int i = 0; i < m_vBody.size(); i++)
    {
        left = m_vBody[i].x * SNAKE_BODYSIZE;
        top = m_vBody[i].y * SNAKE_BODYSIZE;
        right = left + SNAKE_BODYSIZE;
        bottom = top + SNAKE_BODYSIZE;
        pDC->SelectObject(&brush);
        pDC->Rectangle(left, top, right, bottom);
        if (i == 0)
        {
            pDC->Ellipse(left, top, right, bottom);
        }
    }
    DeleteObject(brush);
}

CPoint Snake::GenerateFood()
{
    //TODO: 增加食物的生成
    random_device rd;//随机数生成器
    //mt19937是一个伪随机数生成器，它是 Mersenne Twister 的一个变种。
    mt19937 gen(rd());
    uniform_int_distribution<int> disX(0, GAMEAREA_WIDTH / SNAKE_BODYSIZE - 1);//均匀分布，产生0到指定范围内的整数
    uniform_int_distribution<int> disY(0, GAMEAREA_HEIGHT / SNAKE_BODYSIZE - 1);
    int foodX,foodY;
    do
    {
        foodX = disX(gen);//使用均匀分布产生随机数
        foodY = disY(gen);
    } while (CheckCollision(foodX, foodY));//检查是否有蛇身
    return CPoint(foodX, foodY);
}

CPoint Snake::GenerateFood(Snake& snake)
{
    //TODO: 增加食物的生成
    random_device rd;//随机数生成器
    //mt19937是一个伪随机数生成器，它是 Mersenne Twister 的一个变种。
    mt19937 gen(rd());
    uniform_int_distribution<int> disX(0, GAMEAREA_WIDTH / SNAKE_BODYSIZE - 1);//均匀分布，产生0到指定范围内的整数
    uniform_int_distribution<int> disY(0, GAMEAREA_HEIGHT / SNAKE_BODYSIZE - 1);
    int foodX, foodY;
    do
    {
        foodX = disX(gen);//使用均匀分布产生随机数
        foodY = disY(gen);
    } while (CheckCollision(foodX, foodY) && snake.CheckCollision(foodX, foodY));//检查是否有蛇身
    return CPoint(foodX, foodY);
}

void Snake::AutoDirectionChange(CPoint food)
{
    //TODO: 增加自动移动的功能
    int headX = m_vBody[0].x;
    int headY = m_vBody[0].y;
    int foodX = food.x;
    int foodY = food.y;

    if (headX > foodX && m_Direction != RIGHT)//头在右边，且不向右移动，
    {
        m_Direction = LEFT;//向左移动
    }
    else if (headX < foodX && m_Direction != LEFT)
    {
        m_Direction = RIGHT;
    }
    else if (headY > foodY && m_Direction != DOWN)
    {
        m_Direction = UP;
    }
    else if (headY < foodY && m_Direction != UP)
    {
        m_Direction = DOWN;
    }else
    {
        if(m_Direction==UP||m_Direction==DOWN)
        { 
            m_Direction=rand()%2==0?LEFT:RIGHT;
        }
        else
        {
            m_Direction = rand() % 2 == 0 ? UP : DOWN;
        }
    }
}
  