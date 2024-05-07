/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_point.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_point.h"
#if defined INCLUDED_LIBEX_POINT_H
#if defined __cplusplus_cli
#pragma unmanaged
#endif


#if 000
void  Point::set(                                                          /*M*/
    const pixel_t  x_,                                                     /*-*/
    const pixel_t  y_ ) {                                                  /*-*/
    GO                                                            (UID(F4683B));
    if (EQUALS(x.value, x_) && EQUALS(y.value, y_)) {
        RETURN(NIL);
    }

    if (!this->hasEventHandlers(this)) {
        x.value = x_;
        y.value = y_;
        RETURN(NIL);
    }

    const pixel_t  prev_x = x.value;
    const pixel_t  prev_y = y.value;

    x.value = x_;
    y.value = y_;

    EventData  event(this, PROPERTY_SET);
    this->raiseEvent(event);

    if (event.is_cancelled) {
        x.value = prev_x;
        y.value = prev_y;
    }
    RETURN(NIL);
} /* set */
#endif                                                                 /* 000 */


#if 000
bool  Point::inside( const Rect&  value_ ) const {                         /*M*/
    GO                                                            (UID(F670EF));
    const bool  ret = contains(value_, *this);
    RETURN(ret);
} /* inside */


/* using EventHandler */
void  Point::handleEvent( EventData&  event_ ) {      /* virtual */
    /*E*/
    GO                                                            (UID(F44AB5));
    HANDLE_PROPERTY_SET(x);
    HANDLE_PROPERTY_SET(y);
    RETURN(NIL);
} /* handleEvent */


void  Point::set_x( void ) {                                               /*P*/
} /* set_x */


void  Point::set_y( void ) {                                               /*P*/
} /* set_y */
#endif                                                                 /* 000 */


#endif                                                                   /*eof*/
