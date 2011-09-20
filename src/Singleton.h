/*
    This file is a part of MapMe.

    MapMe is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
 * \file Singleton.h
 * \brief Singleton structure.
 *
 * This file provide a singleton implementation.
 */

#ifndef SINGLETON_H
#define SINGLETON_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <cstdlib>

/* ************************************************************************** */

/*!
 * \class Singleton
 * \brief class for manage other classes
 *
 * This class handle unique classes instance on demand.
 */
template <class T>
class Singleton
{
public:
    /*!
     * \fn static T& getInstance()
     * \return Return a reference to a class instance.
     *
     * Create and/or just return an existing class instance.
     */
    static T& getInstance()
    {
        if (!Inst)
        {
            Inst= new T;
        }

        return *Inst;
    }

    /*!
     * \fn static void destroyInstance()
     *
     * Destroy a class instance by calling it's destructor.
     */
    static void destroyInstance()
    {
        delete Inst;
        Inst= NULL;
    }

protected:
    /*!
     * \fn void Singleton()
     *
     * Empty Singleton constructor.
     */
    Singleton()
    {
        // empty
    }

    /*!
     * \fn void ~Singleton()
     *
     * Empty Singleton destructor.
     */
    ~Singleton()
    {
        std::cout << "Singleton is being destroy !!" << std::endl;
    }

private:
    /*!
     * Class instance
     */
    static T* Inst;

    /*!
     * Forbidden copies
     */
    Singleton(Singleton&);
    void operator= (Singleton&);
};

/*!
 * Declaration of our unique class instance
 */
template <class T> T* Singleton<T>::Inst= NULL;

/* ************************************************************************** */
#endif
