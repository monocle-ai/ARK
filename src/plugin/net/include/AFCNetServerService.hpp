/*
 * This source file is part of ARK
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2019 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFMap.hpp"
#include "base/AFPluginManager.hpp"
#include "log/interface/AFILogModule.hpp"
#include "bus/interface/AFIMsgModule.hpp"
#include "net/interface/AFINetServiceManagerModule.hpp"
#include "net/interface/AFINetServerService.hpp"

namespace ark {

class AFCNetServerService final : public AFINetServerService
{
public:
    explicit AFCNetServerService(AFPluginManager* p);
    //~AFCNetServerService() override;

    bool Start(const AFHeadLength len, const int bus_id, const AFEndpoint& ep, const uint8_t thread_count,
        const uint32_t max_connection) override;
    bool Update() override;

    std::shared_ptr<AFINet> GetNet() override;

    bool RegMsgCallback(const int msg_id, NET_MSG_FUNCTOR&& cb) override;
    bool RegForwardMsgCallback(NET_MSG_FUNCTOR&& cb) override;
    bool RegNetEventCallback(NET_EVENT_FUNCTOR&& cb) override;

protected:
    void OnNetMsg(const AFNetMsg* msg);
    void OnNetEvent(const AFNetEvent* event);

    //void OnClientRegister(const AFNetMsg* msg, const int64_t session_id);
    //void SyncToAllClient(const int bus_id, const AFGUID& session_id);

private:
    AFPluginManager* m_pPluginManager;
    AFINetServiceManagerModule* m_pNetServiceManagerModule;
    AFILogModule* m_pLogModule;
    AFIMsgModule* m_pMsgModule;

    std::shared_ptr<AFINet> m_pNet{nullptr};

    std::map<int, NET_MSG_FUNCTOR> net_msg_callbacks_;
    std::list<NET_MSG_FUNCTOR> net_forward_msg_callbacks_;
    std::list<NET_EVENT_FUNCTOR> net_event_callbacks_;

    //AFMapEx<int, AFServerData> reg_clients_;
};

} // namespace ark
