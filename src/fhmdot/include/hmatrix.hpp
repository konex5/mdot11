#pragma once

#include <boost/filesystem.hpp>

namespace fhmdot
{
    namespace hmatrix
    {
        template <class Q, typename T>
        class mps
        {
        public:
            typedef T value_type;
            typedef Q qnum_type;

            void load(boost::filesystem filename){

            };
            void save(boost::filesystem filename){

            };

        private:
            //std::map<std::tuple<3>, std::vector<value_type>> arr_;
        }

        template <class Q, typename T>
        class mpo
        {

        public:
            typedef T value_type;
            typedef Q qnum_type;

            void load(boost::filesystem filename){

            };
            void save(boost::filesystem filename){

            };

        private:
            //std::map<std::tuple<4>, std::vector<value_type>> arr_;
        }

    } // namespace hmatrix

} // namespace fhmdot
