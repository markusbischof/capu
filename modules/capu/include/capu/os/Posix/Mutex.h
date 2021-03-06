/*
 * Copyright (C) 2012 BMW Car IT GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CAPU_UNIXBASED_MUTEX_H
#define CAPU_UNIXBASED_MUTEX_H

#include <pthread.h>

namespace capu
{
    namespace posix
    {
        //forward declaration in order to use it in friend declaration
        class CondVar;

        class Mutex
        {
        public:
            friend class capu::posix::CondVar;
            Mutex();
            ~Mutex();
            status_t lock();
            bool_t trylock();
            status_t unlock();

        private:
            pthread_mutex_t     mLock;
            pthread_mutexattr_t mLockAttr;
        };

        inline
        Mutex::Mutex()
        {
            pthread_mutexattr_init(&mLockAttr);
            pthread_mutexattr_settype(&mLockAttr, PTHREAD_MUTEX_RECURSIVE);
            pthread_mutex_init(&mLock, &mLockAttr);
        }

        inline
        Mutex::~Mutex()
        {
            pthread_mutex_destroy(&mLock);
            pthread_mutexattr_destroy(&mLockAttr);
        }

        inline
        status_t
        Mutex::lock()
        {
            if (pthread_mutex_lock(&mLock) == 0)
            {
                return CAPU_OK;
            }
            else
            {
                return CAPU_ERROR;
            }
        }

        inline
        status_t
        Mutex::unlock()
        {
            if (pthread_mutex_unlock(&mLock) == 0)
            {
                return CAPU_OK;
            }
            else
            {
                return CAPU_ERROR;
            }
        }

        inline
        bool
        Mutex::trylock()
        {
            if (pthread_mutex_trylock(&mLock) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

#endif // CAPU_UNIXBASED_MUTEX_H
