#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE DhcpTests
#endif
#include <boost/asio.hpp>
#include <boost/test/unit_test.hpp>
#include "AssignedAddresses.h"
#include "AssignedAddress.h"
#include <thread>

BOOST_AUTO_TEST_SUITE(AssignedAddressesMutexTests)
    BOOST_AUTO_TEST_CASE(AddingAddressesInTwoThreads) {
        AssignedAddresses assignedAddresses;
        auto worker = [](AssignedAddresses& assignedAddresses) {
            AssignedAddress assigned;
            assigned.ip = boost::asio::ip::address_v4::from_string("127.0.0.1");
            for(size_t index = 0; index< 10000; index++) {
                assignedAddresses.push(assigned);
            }
        };

        std::thread threadOne{worker,std::ref(assignedAddresses)};
        std::thread threadTwo{worker,std::ref(assignedAddresses)};

        threadOne.join();
        threadTwo.join();
    }

    BOOST_AUTO_TEST_CASE(AddingDeletingAddressesThreads) {
        AssignedAddresses assignedAddresses;

        auto addingWorker = [](AssignedAddresses& assignedAddresses) {
            AssignedAddress assigned;
            assigned.ip = boost::asio::ip::address_v4::from_string("127.0.0.1");
            for(size_t index = 0; index< 10000; index++) {
                assignedAddresses.push(assigned);
            }
        };

        auto removingWorker = [](AssignedAddresses& assignedAddresses) {
            AssignedAddress assigned;
            assigned.ip = boost::asio::ip::address_v4::from_string("127.0.0.1");
            for(size_t index = 0; index< 10000; index++) {
                assignedAddresses.remove(boost::asio::ip::address_v4::from_string("127.0.0.1"));
            }
        };

        std::thread threadOne{addingWorker,std::ref(assignedAddresses)};
        std::thread threadTwo{removingWorker,std::ref(assignedAddresses)};

        threadOne.join();
        threadTwo.join();
    }
BOOST_AUTO_TEST_SUITE_END()