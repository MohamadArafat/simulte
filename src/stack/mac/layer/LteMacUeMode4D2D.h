//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef STACK_MAC_LAYER_LTEMACUEMODE4D2D_H_
#define STACK_MAC_LAYER_LTEMACUEMODE4D2D_H_

#include "stack/mac/layer/LteMacUeRealisticD2D.h"
#include "corenetwork/deployer/LteDeployer.h"
#include <random>

//class LteMode4SchedulingGrant;

class LteMacUeMode4D2D: public LteMacUeRealisticD2D {

protected:

   /// Lte AMC module
   LteAmc *amc_;

   /// Local LteDeployer
   LteDeployer *deployer_;

   int numAntennas_;

   // RAC Handling variables
   bool racD2DMulticastRequested_;
   // Multicast D2D BSR handling
   bool bsrD2DMulticastTriggered_;

   // All of the following should be configurable by the OMNet++ ini file and maybe even taken from higher layers if that's possible.
   double probResourceKeep_;
   int resourceReservationInterval_;
   int minSubchannelNumberPSSCH_;
   int maxSubchannelNumberPSSCH_;
   int maximumLatency_;
   int subchannelSize_;
   int numSubchannels_;
   int minMCSPSSCH_;
   int maxMCSPSSCH_;
   int maximumCapacity_;
   int allowedRetxNumberPSSCH_;
   int reselectAfter_;
   int defaultCbrIndex_;
   bool useCBR_;
   int cbr_;

   std::map<UnitList, int> pduRecord_;

   std::vector<std::map<std::string, int>> cbrPSSCHTxConfigList_;
   std::vector<std::map<std::string, int>> cbrLevels_;
   std::vector<int> validResourceReservationIntervals_;

   // if true, use the preconfigured TX params for transmission, else use that signaled by the eNB
   bool usePreconfiguredTxParams_;
   UserTxParams* preconfiguredTxParams_;
   UserTxParams* getPreconfiguredTxParams();  // build and return new user tx params

   std::random_device rand_dev;
   std::mt19937 generator;

//   // Lte AMC module
//   LteAmc *amc_;

    /**
     * Getter for Deployer.
     */
    virtual LteDeployer* getDeployer();

    /**
     * Returns the number of system antennas (MACRO included)
     */
    virtual int getNumAntennas();

    /**
     * Generate a scheduling grant
     */
    virtual void macGenerateSchedulingGrant();


    /**
     * Handles the SPS candidate resources message from the PHY layer.
     */
    virtual void macHandleSps(cPacket* pkt);

    /**
     * Reads MAC parameters for ue and performs initialization.
     */
    virtual void initialize(int stage);

    /**
     * Analyze gate of incoming packet
     * and call proper handler
     */
    virtual void handleMessage(cMessage *msg);

    /**
     * Main loop
     */
    virtual void handleSelfMessage();

    /**
     * macPduMake() creates MAC PDUs (one for each CID)
     * by extracting SDUs from Real Mac Buffers according
     * to the Schedule List.
     * It sends them to H-ARQ (at the moment lower layer)
     *
     * On UE it also adds a BSR control element to the MAC PDU
     * containing the size of its buffer (for that CID)
     */
    virtual void macPduMake();

    /**
     * Parse transmission configuration for a Ue
     */
    void parseUeTxConfig(cXMLElement* xmlConfig);

    /**
     * Parse transmission configuration for CBR
     */
    void parseCbrTxConfig(cXMLElement* xmlConfig);

    /**
     * Parse transmission configuration for Resource Reservation Intervals
     */
    void parseRriConfig(cXMLElement* xmlConfig);

    /**
     * Purges PDUs from the HARQ buffers for sending to the PHY layer.
     */
    void flushHarqBuffers();

public:
    LteMacUeMode4D2D();
    virtual ~LteMacUeMode4D2D();

    virtual bool isD2DCapable()
    {
        return true;
    }
};

#endif /* STACK_MAC_LAYER_LTEMACUEMODE4D2D_H_ */
