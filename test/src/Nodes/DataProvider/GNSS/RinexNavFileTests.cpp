// This file is part of INSTINCT, the INS Toolkit for Integrated
// Navigation Concepts and Training by the Institute of Navigation of
// the University of Stuttgart, Germany.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include <catch2/catch.hpp>

#include "FlowTester.hpp"
#include "util/Logger.hpp"

#include "internal/NodeManager.hpp"
namespace nm = NAV::NodeManager;

#include "NodeData/GNSS/GnssNavInfo.hpp"

namespace NAV::TEST::RinexNavFileTests
{

TEST_CASE("[RinexNavFile] Read v3.03 Files and check correctness", "[RinexNavFile][flow][Debug]")
{
    Logger logger;

    // ###########################################################################################################
    //                                             RinexNavFile.flow
    // ###########################################################################################################
    //
    //  RinexNavFile("Skydel-static_4h_1min-rate/SkydelRINEX_S_2022152120_7200S_GN.rnx") (2)
    //                                                                    (1) GnssNavInfo <>
    //  RinexNavFile("Skydel-static_4h_1min-rate/SkydelRINEX_S_2022152120_600S_EN") (4)
    //                                                                    (5) GnssNavInfo <>
    //  RinexNavFile("Skydel-static_4h_1min-rate/SkydelRINEX_S_2022152120_1800S_RN.rnx") (7)
    //                                                                    (6) GnssNavInfo <>
    //  RinexNavFile("Skydel-static_4h_1min-rate/SkydelRINEX_S_2022152120_120S_SN") (13)
    //                                                                   (12) GnssNavInfo <>
    //
    // ###########################################################################################################

    nm::RegisterCleanupCallback([]() {
        auto* gpsPin = nm::FindOutputPin(1);
        REQUIRE(gpsPin != nullptr);

        const auto* gnssNavInfo_GPS = static_cast<const GnssNavInfo*>(std::get<const void*>(gpsPin->data));

        REQUIRE(gnssNavInfo_GPS->broadcastEphemeris.size() == 32);
        for (const auto& ephOfSat : gnssNavInfo_GPS->broadcastEphemeris)
        {
            REQUIRE(ephOfSat.second.size() == 3);
        }

        // TODO: Write the actual test here
    });

    testFlow("test/flow/Nodes/DataProvider/GNSS/RinexNavFile.flow");
}

} // namespace NAV::TEST::RinexNavFileTests