#pragma once

namespace n_circle {
	//��
	class ClCircle
	{
	public:
		ClCircle();
		~ClCircle();

	private:
		n_xy::XY m_center;
		int m_radius;
	};
}