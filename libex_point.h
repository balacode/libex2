/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                       [libex_point.h] */
/* -------------------------------------------------------------------------- */

#if !defined INCLUDED_LIBEX_POINT_H
#define      INCLUDED_LIBEX_POINT_H

typedef struct  Point {
    int  dummy;
}
Point;

Point*  lx_Point_construct( );                                             /*C*/

void  lx_Point_destroy(Point*  object_ );                                  /*D*/

#if 000

/* Defines a 2-dimensional coordinate point. */
struct Point {
public:
    LX_NUMERIC_PROPERTY(x, lx_pixel_t);  /* x-axis coordinate. */
    LX_NUMERIC_PROPERTY(y, lx_pixel_t);  /* y-axis coordinate. */

    /* Default Constructor */
    inline Point(                                                          /*C*/
        const lx_pixel_t  x_ = 0,                                          /*-*/
        const lx_pixel_t  y_ = 0 )                                         /*-*/
        :
        EventEmitter (),
        EventHandler (),
        x            (x_),
        y            (y_) {
        LX_GO                                                  (LX_UID(CEFF7B));
        _SET_HANDLERS;
        LX_RETURN(LX_NIL);
    } /* Point */

    /* Copy Constructor */
    inline Point( const Point&   init_ )                                   /*C*/
        :
        EventEmitter (init_),
        EventHandler (),
        x            (init_.x.value),
        y            (init_.y.value) {
        LX_GO                                                  (LX_UID(C56950));
        _SET_HANDLERS;
        LX_RETURN(LX_NIL);
    } /* Point */

#undef _SET_HANDLERS

    /* Destructor: */
    inline virtual  ~Point( ) {                                            /*D*/
        LX_GO                                                  (LX_UID(D97901));
        LX_RETURN(LX_NIL);
    } /* ~Point */

    /* Assignment Operator */
    inline Point&  operator = ( const Point&   copy_from_ ) {              /*O*/
        LX_GO                                                  (LX_UID(FEB876));
        this->set(copy_from_.x.value, copy_from_.y.value);
        LX_RETURN(*this);
    } /* operator = */

    /* Comparison Operators */

    /* returns true if the coordinates of two points are equal. */
    inline bool  operator == ( const Point&   value_ ) const {             /*O*/
        LX_GO                                                  (LX_UID(F6BB65));
        const bool  ret = LX_EQUALS(x.value, value_.x.value) &&
                          LX_EQUALS(y.value, value_.y.value);
        LX_RETURN(ret);
    } /* operator == */

    /* returns true if the coordinates of two points are not equal. */
    inline bool  operator != ( const Point&   value_ ) const {             /*O*/
        LX_GO                                                  (LX_UID(F2AC20));
        const bool  ret = !this->operator == (value_);
        LX_RETURN(ret);
    } /* operator != */

public:  /* Methods: */

    /* Resets the point's x and y coordinates to zero. */
    inline void  clear( ) {                                                /*M*/
        LX_GO                                                  (LX_UID(FE9AF1));
        x.value = y.value = 0;
        LX_RETURN(LX_NIL);
    } /* clear */

    /* Sets this point's coordinates. */
    void  set(                                                             /*M*/
        const lx_pixel_t  x_,                                              /*-*/
        const lx_pixel_t  y_ );                                            /*-*/

    /* Sets this point's coordinates from another point. */
    inline void  set( const Point&   value_ ) {                            /*M*/
        LX_GO                                                  (LX_UID(F81BF9));
        set(value_.x.value, value_.y.value);
        LX_RETURN(LX_NIL);
    } /* set */

    /* returns true if this point lies within  */
    /* the coordinates of the given rectangle. */
    bool  inside( const Rect&   value_ ) const;                            /*P*/

    /* Main method of EventHandler */
    virtual void  handleEvent( EventData&   event_ );                      /*E*/
}
Point;
#endif                                                                 /* 000 */

#endif                                                                   /*eof*/
