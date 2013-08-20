// This file is part of SpaceVecAlg.
//
// SpaceVecAlg is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SpaceVecAlg is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with SpaceVecAlg.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

namespace sva
{

using namespace Eigen;

/**
	* Spatial Motion Vector compact representations.
	* See Roy Featherstone «Rigid Body Dynamics Algorithms» page 247.
	*/
template<typename T>
class MotionVec
{
public:
	typedef Vector3<T> vector3_t;
	typedef Vector6<T> vector6_t;

public:
	MotionVec():
		mv_()
	{}

	/**
		* @param vec Spatial motion vector with angular motion in head
		* and linear motion in tail.
		*/
	MotionVec(const vector6_t& vec):
		mv_(vec)
	{}

	/**
		* @param angular Angular motion.
		* @param linear Linear motion.
		*/
	MotionVec(const vector3_t& angular, const vector3_t& linear):
		mv_((vector6_t() << angular, linear).finished())
	{}

	// Accessor
	/// @return Angular motion part (3 first parameters).
	vector3_t angular() const
	{
		return mv_.template head<3>();
	}

	/// @return Linear motion part (3 last parameters).
	vector3_t linear() const
	{
		return mv_.template tail<3>();
	}

	/// @return Non compact spatial motion vector.
	const vector6_t& vector() const
	{
		return mv_;
	}

	/// @return Non compact spatial motion vector.
	vector6_t& vector()
	{
		return mv_;
	}

	template<typename T2>
	MotionVec<T2> cast() const
	{
		return MotionVec<T2>(mv_.cast<T2>());
	}

	// Operators
	MotionVec<T> operator+(const MotionVec<T>& mv) const
	{
		return MotionVec<T>(mv_ + mv.mv_);
	}

	MotionVec<T> operator-(const MotionVec<T>& mv) const
	{
		return MotionVec<T>(mv_ - mv.mv_);
	}

	MotionVec<T> operator-() const
	{
		return MotionVec<T>(-mv_);
	}

	template<typename T2>
	MotionVec<T> operator*(T2 scalar) const
	{
		return MotionVec<T>(scalar * mv_);
	}

	/// @return v x v
	MotionVec<T> cross(const MotionVec<T>& mv2) const;

	/// @return v x* f
	ForceVec<T> crossDual(const ForceVec<T>& fv2) const;

	/// @return v.v
	double dot(const ForceVec<T>& fv2) const;


	bool operator==(const MotionVec<T>& mv) const
	{
		return mv_ == mv.mv_;
	}

	bool operator!=(const MotionVec<T>& mv) const
	{
		return mv_ != mv.mv_;
	}

private:
	vector6_t mv_;
};

template<typename T, typename T2>
inline MotionVec<T> operator*(T2 scalar, const MotionVec<T>& mv)
{
	return mv*scalar;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const MotionVec<T>& mv)
{
	out << mv.vector().transpose();
	return out;
}

} // namespace sva
