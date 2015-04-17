#ifndef _EVENT_EXT_H
#define _EVENT_EXT_H 1

#include "openflow/openflow.h"
#include "openvswitch/types.h"

#define EPCC_VENDOR_ID 0xEBCC3118

struct evt_header{
    struct ofp_header header;
    ovs_be32 vendor;
    ovs_be32 subtype;
};

enum evt_event_type{
    EVT_PORT_STATS_TIMER_TRIGGER = 0x01,
    EVT_FLOW_STATS_TIMER_TRIGGER = 0x03,
};

struct evt_flow_timer_config{
    uint32_t interval_sec;
    uint32_t interval_msec;


};

enum evt_event_id{
    EVT_EVENT_ID_MAX = 0xffffff00,
    EVT_EVENT_ID_ERR = 0xfffffff0,
};

enum evt_event_request_type{
    EVT_EVENT_ADD     = 0x01,
    EVT_EVENT_MODIFY  = 0x02,
    EVT_EVENT_DELETE  = 0x03
};

enum evt_event_periodic{
    EVT_PERIODIC   = 0x01,
    EVT_ONLY_FIRST = 0x02,
};

enum evt_port_condition{
    EVT_CONDITION_TX_PACKETS = 0x01,
    EVT_CONDITION_TX_BYTES   = 0x02,
    EVT_CONDITION_RX_PACKETS = 0x04,
    EVT_CONDITION_RX_BYTES   = 0x08,
};

enum evt_flow_condition{
    EVT_CONDITION_MATCH_PACKETS = 0x01,
    EVT_CONDITION_MATCH_BYTES   = 0x02,
    EVT_CONDITION_TOTAL_MATCH_PACKETS = 0x04,
    EVT_CONDITION_TOTAL_MATCH_BYTES   = 0x08,
};

struct evt_event_request_header{

    
    uint8_t  request_type;
    uint8_t  periodic;
    ovs_be16 event_type;
    ovs_be32 event_id;
};

struct evt_event_request_port_timer{
    
    uint8_t  request_type;
    uint8_t  periodic;
    ovs_be16 event_type;
    ovs_be32 event_id;
    ovs_be16 check_port;
    ovs_be16 event_conditions;
    ovs_be32 interval_sec;
    ovs_be32 interval_msec;
    ovs_be64 threshold_tx_packets;
    ovs_be64 threshold_tx_bytes;
    ovs_be64 threshold_rx_packets;
    ovs_be64 threshold_rx_bytes;
};

struct evt_event_request_flow_timer{
    
    uint8_t  request_type;
    uint8_t  periodic;
    ovs_be16 event_type;
    ovs_be32 event_id;
    struct ofp10_match match;
    uint8_t table_id;
    uint8_t pad;
    ovs_be16 out_port;
    ovs_be64 flow_cookie;
    ovs_be64 cookie_mask;
    ovs_be16 event_conditions;
    uint8_t pad2[2];
    ovs_be32 interval_sec;
    ovs_be32 interval_msec;
    ovs_be64 threshold_match_packets;
    ovs_be64 threshold_match_bytes;
    ovs_be64 threshold_total_match_packets;
    ovs_be64 threshold_total_match_bytes;
};


enum evt_event_reply_status{
    EVT_STATUS_ADDED       = 0x01,
    EVT_STATUS_MODIFIED    = 0x02,
    EVT_STATUS_REMOVED     = 0x03,
    
    EVT_STATUS_UNSUPPORTED = 0x05,
    EVT_STATUS_NO_PORT     = 0x06,
    EVT_STATUS_NO_FLOW     = 0x07,


    EVT_STATUS_WRONG_EVENT_TYPE = 0x0e,
    EVT_STATUS_NO_EVENT_ID = 0x0f,

    EVT_STATUS_UNKNOWN_ERROR = 0xffff,
};


struct evt_event_reply_msg{
    ovs_be16 event_status;
    ovs_be16 event_type;
    ovs_be32 event_id;
};

enum evt_report_reason{
    EVT_REASON_TRIGGERED = 0x01,
};

struct evt_event_report_header{
    ovs_be16 report_reason;
    ovs_be16 event_type;
    ovs_be32 event_id;
};

struct evt_event_single_port_report{
    ovs_be16 port_no;
    uint8_t pad[2];
    ovs_be32 interval_sec;
    ovs_be32 interval_msec;
    ovs_be64 new_tx_packets;
    ovs_be64 new_tx_bytes;
    ovs_be64 new_rx_packets;
    ovs_be64 new_rx_bytes;
    ovs_be64 total_tx_packets;
    ovs_be64 total_tx_bytes;
    ovs_be64 total_rx_packets;
    ovs_be64 total_rx_bytes;
};

struct evt_event_flow_timer_report_header{
    struct ofp10_match match;
    uint8_t table_id;
    uint8_t pad;
    ovs_be16 out_port;    

    ovs_be32 interval_sec;
    ovs_be32 interval_msec;
};
 
struct evt_event_single_flow_report{

    ovs_be16 length;
    uint8_t table_id;
    uint8_t pad;
    struct ofp10_match match;

    ovs_be64 flow_cookie;

    ovs_be32 duration_sec;
    ovs_be32 duration_nsec;

    ovs_be64 new_match_packets;
    ovs_be64 new_match_bytes;

    ovs_be64 total_match_packets;
    ovs_be64 total_match_bytes;
};

#endif