#ifndef CGRANDMASTER_H
#define CGRANDMASTER_H


class CGrandMaster
{
public:
    CGrandMaster();
    virtual void hello() = 0;

    void song();

private:
    int m_height;
    int m_weight;
};

#endif // CGRANDMASTER_H
