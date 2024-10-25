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
    //�����ߣ�����ʳ��
    m_vBody.clear();
    m_vBody.push_back(CPoint(10, row));
    m_vBody.push_back(CPoint(9, row));
    m_vBody.push_back(CPoint(8, row));

    m_LastDirectionChangeTime =::GetTickCount();
}

BOOL Snake::Move(CPoint food)
{
    //��ȡ��ͷ�ķ���--���⣺�������ٶȳ������ߵ��ƶ��ٶȣ�������ͷ����׼ȷ
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
    //�����ͷ�Ƿ���ײ
    if (CheckCollision(headX, headY))
    {
        return FALSE;
    }
    //������ͷ
    m_vBody.insert(m_vBody.begin(), CPoint(headX, headY));//ͷ�����뵽����ͷ
    //����Ƿ�Ե�ʳ��
    if (CheckFood(food))
    {
        //�Ե�ʳ��
        m_bGrow = TRUE;
    }
    else
    {
        //ɾ��β��
        m_vBody.pop_back();
        m_bGrow = FALSE;
    }
    return TRUE;
}

BOOL Snake::CheckCollision(int x,int y) const
{
    //TODO: �����������ײ���
    BOOL collision= FALSE;
    // C++ �ı�׼���㷨 any_of���书���Ǽ�������Χ���Ƿ����κ�Ԫ�������ض�������
    //any_of ��һ���㷨��������һ�Ե�������һ��ν�ʣ�������������ڵ�����Χ���ҵ�����һ��Ԫ��ʹ��ν�ʷ��� true���� any_of ���� true�����򷵻� false��
    //lambda���ʽ���﷨���£�[x,y]�����б���CPoint p�������б���ʾ��ǰ���ڱ�����Ԫ�أ�����ֵ�ǲ���ֵ��
    if (any_of(m_vBody.begin(), m_vBody.end(), [x, y](CPoint p) { return p.x == x && p.y == y; }))
    {
        collision = TRUE;
    }
    //���Ƿ������߽�
    if (x < 0 || x >= GAMEAREA_WIDTH / SNAKE_BODYSIZE || y < 0 || y >= GAMEAREA_HEIGHT / SNAKE_BODYSIZE)
    {
        collision = TRUE;
    }
    return collision;
}

BOOL Snake::CheckFood(CPoint food)
{
    //TODO: ����ʳ��ļ��
    return (m_vBody[0].x == food.x && m_vBody[0].y == food.y);
}

void Snake::SetDirection(Direction dir)
{
    //TODO: ���ӷ��������--���ܵ�ͷ
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
    //TODO: ��������Ļ���
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
    //TODO: ����ʳ�������
    random_device rd;//�����������
    //mt19937��һ��α����������������� Mersenne Twister ��һ�����֡�
    mt19937 gen(rd());
    uniform_int_distribution<int> disX(0, GAMEAREA_WIDTH / SNAKE_BODYSIZE - 1);//���ȷֲ�������0��ָ����Χ�ڵ�����
    uniform_int_distribution<int> disY(0, GAMEAREA_HEIGHT / SNAKE_BODYSIZE - 1);
    int foodX,foodY;
    do
    {
        foodX = disX(gen);//ʹ�þ��ȷֲ����������
        foodY = disY(gen);
    } while (CheckCollision(foodX, foodY));//����Ƿ�������
    return CPoint(foodX, foodY);
}

CPoint Snake::GenerateFood(Snake& snake)
{
    //TODO: ����ʳ�������
    random_device rd;//�����������
    //mt19937��һ��α����������������� Mersenne Twister ��һ�����֡�
    mt19937 gen(rd());
    uniform_int_distribution<int> disX(0, GAMEAREA_WIDTH / SNAKE_BODYSIZE - 1);//���ȷֲ�������0��ָ����Χ�ڵ�����
    uniform_int_distribution<int> disY(0, GAMEAREA_HEIGHT / SNAKE_BODYSIZE - 1);
    int foodX, foodY;
    do
    {
        foodX = disX(gen);//ʹ�þ��ȷֲ����������
        foodY = disY(gen);
    } while (CheckCollision(foodX, foodY) && snake.CheckCollision(foodX, foodY));//����Ƿ�������
    return CPoint(foodX, foodY);
}

void Snake::AutoDirectionChange(CPoint food)
{
    //TODO: �����Զ��ƶ��Ĺ���
    int headX = m_vBody[0].x;
    int headY = m_vBody[0].y;
    int foodX = food.x;
    int foodY = food.y;

    if (headX > foodX && m_Direction != RIGHT)//ͷ���ұߣ��Ҳ������ƶ���
    {
        m_Direction = LEFT;//�����ƶ�
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
  