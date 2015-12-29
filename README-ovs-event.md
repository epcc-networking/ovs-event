#Usage: build and run ovs-event in the sameway as using OVS.
=============================================================
# Changed files of OpenEvent to OVS:
========================================
## 1) Added epcc-ext.h in include/openflow.
This header file specifies the messages in OpenEvent.
---
## 2) modified lib/ofp-msgs.h:
### added new raw message type:
OFPRAW_EPCC_EVENT_REQUEST, OFPRAW_EPCC_EVENT_REPLY,OFPRAW_EPCC_EVENT_REPORT
for raw OpenFlow message types event request, event reply, event report
### new message type:
OFPTYPE_EPCC_EVENT_REQUEST, OFPTYPE_EPCC_EVENT_REPLY, OFPTYPE_EPCC_EVENT_REPORT
for messages in ofproto
---
## 3) modified lib/ofp-msgs.c:
added statements to decode vendor headers of messages in OpenEvent
OFPTYPE_EPCC_EVENT_REQUEST, OFPTYPE_EPCC_EVENT_REPLY, OFPTYPE_EPCC_EVENT_REPORT)
---
## 4) modified lib/ofp-util.h & lib/ofp-util.c:
### lib/ofp-util.h(at last part of the file):
added struct ofputil_event_request_header for header of event requests
added struct ofputil_event_request_port_timer and 
struct ofputil_event_request_flow_timer 
for requests of port events and flow events
--
### lib/ofp-util.c(at the last part of the file,L):
added functions:
ofputil_decode_event_request, ofputil_decode_event_request_port_timer, 
ofputil_decode_ofp10_event_request_flow_timer, ofputil_decode_ofp11_event_request_flow_timer
to decode event requests
added function:
ofputil_encode_event_reply to encode event replies
added functions:
ofputil_encode_event_port_timer_report, ofputil_encode_event_flow_timer_report,
ofputil_encode_ofp10_event_flow_timer_report,ofputil_encode_ofp11_event_flow_timer_report,
to encode event reports.
---
## 5) added event-struct.h in ofproto. 
this file defines port event and flow event in ofproto 
in struct event_port_timer and struct event_flow_timer.
---
## 6) modified ofproto/ofproto-provider.h.
added event list in struct ofproto in L114: struct ovs_list 
---
## 7) modified ofproto/ofproto.c.
added initialization of event table in function ofproto_create():L578 
added deletion of events in function ofproto_destry(): L1559

### added functions to process events, starting at L6435
added function alloc_event_id() to assign event IDs to events: L6437
added function event_wait() to wake up when events should be checked: L6779
added function ofproto_event_delete(),ofproto_event_delete_by_id to delete events: L6503
added function handle_event_add(),handle_event_modify(),handle_event_delete(),handle_event_request()
to handle requests to add, modify, or delete an event: L6564
added functions event_flow_timer_check(),event_port_timer_check() 
to check events on flow stats and events on port stats
added function ofproto_event_run() to traverse the event list and call functions to check events
when there are events should be checked: L7064

added calling of event_wait() in ofproto_wait(): L1752
added calling of ofproto_event_run() in ofproto_run(): L1699
---
## 8) modified script build-aux/extract-ofp-msgs:
added EPCC_VENDOR_ID = 0xebcc3118 for messages in OpenEvent: L20
added code to extract headers of messages in OpenEvent: L199 

