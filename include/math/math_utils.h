#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__ 1

class MathUtils {
	public:
		static float Clamp(float value, float minVal, float maxVal);

	private:
		MathUtils();
		MathUtils(const MathUtils& copy);
		~MathUtils();
};
inline MathUtils::MathUtils() {}
inline MathUtils::MathUtils(const MathUtils& copy) {
	*this = copy;
}
inline MathUtils::~MathUtils(){}

// Author: Alan Gutierrez Ramirez
inline float MathUtils::Clamp(float value, float minVal, float maxVal) {
	if (value >= maxVal)
	{
		return maxVal;
	}
	if (value <= minVal)
	{
		return minVal;
	}
	return value;
}
#endif
