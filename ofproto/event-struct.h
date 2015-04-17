#ifndef _EVENT_STRUCT_H
#define _EVENT_STRUCT_H

#include "openflow/event-ext.h"
#include "match.h"
#include "list.h"
#include "ofproto-provider.h"

struct event_port_timer{
    
    long long int next_check_time;
    
    uint32_t interval_sec;
    uint32_t interval_msec;

    ofp_port_t check_port;
    uint16_t event_conditions;

    uint64_t threshold_tx_packets;
    uint64_t threshold_tx_bytes;
    uint64_t threshold_rx_packets;
    uint64_t threshold_rx_bytes;

    uint64_t prev_tx_packets;
    uint64_t prev_tx_bytes;
    uint64_t prev_rx_packets;
    uint64_t prev_rx_bytes;
};

struct event_single_flow{
    bool exist;
    struct rule *rule;

    uint64_t prev_match_packets;
    uint64_t prev_match_bytes;

    uint64_t additional_match_packets;
    uint64_t additional_match_bytes;

    //struct ovs_list list_node;
    struct hmap_node hmap_node;
};

struct event_flow_timer{
    long long int next_check_time;

    uint32_t interval_sec;
    uint32_t interval_msec;

    ofp_port_t out_port;
    uint8_t table_id;    
    
    struct match match;

    ovs_be64 flow_cookie;
    ovs_be64 cookie_mask;

    uint16_t event_conditions;

    uint64_t threshold_match_packets;
    uint64_t threshold_match_bytes;
    uint64_t threshold_total_match_packets;
    uint64_t threshold_total_match_bytes;

    //struct ovs_list single_flows;
    struct hmap single_flows;
};

struct event{
    struct ovs_list event_list_node;
    uint32_t event_id;
    long long int time_created;
    uint32_t times_triggered;
    enum evt_event_type event_type;
    bool periodic;

    struct event_port_timer *port_timer;
    struct event_flow_timer *flow_timer;
    
};

#endif