#pragma once
#define SNAKE_BODYSIZE 40
#define GAMEAREA_WIDTH 800
#define GAMEAREA_HEIGHT 800

enum Direction { UP, DOWN, LEFT, RIGHT };//定义方向枚举
class Snake
{
public:
    Snake();
    ~Snake();

    void Init(int row);
    BOOL Move(CPoint food);
    BOOL CheckCollision(int x, int y) const;
    BOOL CheckFood(CPoint food);
    void SetDirection(Direction dir);
    BOOL IsGrow();
    void Draw(CDC* pDC, COLORREF color);
    CPoint GenerateFood();
    CPoint GenerateFood(Snake& snake);
    void AutoDirectionChange(CPoint food);
public:
    // 在类定义中增加一个变量--限制方向变更频率 
    DWORD m_LastDirectionChangeTime = 0;
    DWORD m_DirectionChangeInterval = 200;
private:
        vector<CPoint> m_vBody;
        Direction m_Direction;
        BOOL m_bGrow;
};

