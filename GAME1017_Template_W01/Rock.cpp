#include "Rock.h"
#include "MathManager.h"

void Rock::Update()
{
	m_dst.x = MAMA::LerpD(m_dst.x, m_dst.x - 5, 0.1);	
}
