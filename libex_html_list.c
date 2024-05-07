/* -------------------------------------------------------------------------- */
/* (c) ali@balarabe.com                                   [libex_html_list.c] */
/* -------------------------------------------------------------------------- */

#include "libex_c_precompiled.h"
#include "libex_html_list_.h"
#if defined INCLUDED_LIBEX_HTML_LIST_H

#include <string.h>  /* for memset() */

#include "libex_.h"
#include "libex_array_.h"
#include "libex_call_.h"
#include "libex_const_.h"
#include "libex_debug_.h"
#include "libex_error_.h"
#include "libex_stringc_.h"

#if defined __cplusplus_cli
#pragma unmanaged
#endif


/* -------------------------------------------------------------------------- */
NAMESPACE(c_)


/* -------------------------------------------------------------------------- */
/* Structures:                                                                */


typedef struct  _col_t {
    new_chars_t  heading;                                           /* _col_t */
    new_chars_t  data_type;                                         /* _col_t */
    new_chars_t  field_name;                                        /* _col_t */
}
_col_t;


typedef struct  _html_list_t {
    /* public $fallback_href = '';          */
    /* public $fIncludeTemplateRow_ = true; */

    new_chars_t  key_field;                                   /* _html_list_t */
    new_chars_t  href_delete;                                 /* _html_list_t */
    new_chars_t  href_edit;                                   /* _html_list_t */
    new_chars_t  href_new;                                    /* _html_list_t */
    new_chars_t  summary_row;                                 /* _html_list_t */
    array_t      columns;                                     /* _html_list_t */
}
_html_list_t;


/* -------------------------------------------------------------------------- */
/* Methods: Private                                                           */


#define _BASE_OBJ_WRAP_INC
#define _OBJ_HANDLE_TYPE   HtmlList
#define _OBJ_INNER_TYPE    _html_list_t
#define _OBJ_ALLOC_FN_UID  UID(FE3866)
#define _OBJ_FREE_FN_UID   UID(F5BA18)
#define _OBJ_CONST_FN_UID  UID(F64F58)
#define _OBJ_FN_UID        UID(F6A6F0)
#define _OBJ_WRAP_FN_UID   UID(FD6FD4)
#include "libex_object_wrapper.inc.c"


/* -------------------------------------------------------------------------- */
/* Constructor:                                                               */


PUBLIC new_HtmlList  HtmlList_init( void ) {                               /*C*/
    GO                                                            (UID(F8085E));
    _html_list_t*  ob  = _object_alloc();
    new_HtmlList   ret = _object_wrap(ob);
    ob->columns = Array_init(sizeof(_col_t), 25, 0);
    RETURN(ret);
} /* HtmlList_init */


/* -------------------------------------------------------------------------- */
/* Destructor:                                                                */


PUBLIC void  HtmlList_free( HtmlList*  object_ ) {                         /*D*/
    GO                                                            (UID(F2208D));
    _html_list_t* const  me = _object(object_, UID(EC2D0A));

    /* release strings */
    freeT(&me->key_field);
    freeT(&me->href_delete);
    freeT(&me->href_edit);
    freeT(&me->href_new);
    freeT(&me->summary_row);

    {
        /* release arrays: */
        const size_t  count = Array_count(me->columns);
        size_t        i     = 0;
        for (i = 0; i < count; i++) {
            _col_t*  col = CAST(_col_t*, Array_getItemAt(&me->columns, i));
            freeT(&col->heading);
            freeT(&col->data_type);
            freeT(&col->field_name);
        }
    }
    Array_removeItems(&me->columns);
    _object_free(object_);
    RETURN(NIL);
} /* HtmlList_free */


/* -------------------------------------------------------------------------- */
/* Properties:                                                                */


PUBLIC chars_t  HtmlList_getKeyField( HtmlList  object_ ) {                /*P*/
    GO                                                            (UID(F7A7BC));
    _html_list_t* const  me  = _object(&object_, UID(EFA992));
    chars_t              ret = me->key_field != NULL ? me->key_field : BLANK;
    RETURN(ret);
} /* HtmlList_getKeyField */


PUBLIC void  HtmlList_setKeyField(                                         /*P*/
    HtmlList  object_,                                                     /*-*/
    chars_t   value_ ) {                                                   /*-*/
    GO                                                            (UID(FAF1AF));
    _html_list_t* const  me = _object(&object_, UID(EDC56A));
    freeT(&me->key_field);
    me->key_field = T_chars(value_);
    RETURN(NIL);
} /* HtmlList_setKeyField */


END_NAMESPACE  /*c_*/
#endif                                                                   /*eof*/


#if 000
public function set_summary_row_(                                          /*F*/
    $column_1_s_, $column_2_s_ = null, $column_3_s_ = null,
    $column_4_s_  = null, $column_5_s_  = null, $column_6_s_  = null,
    $column_7_s_  = null, $column_8_s_  = null, $column_9_s_  = null,
    $column_10_s_ = null, $column_11_s_ = null, $column_12_s_ = null,
    $column_13_s_ = null, $column_14_s_ = null, $column_15_s_ = null) {
    $html = html_table_row(
                $column_1_s_,  $column_2_s_,  $column_3_s_,
                $column_4_s_,  $column_5_s_,  $column_6_s_ ,
                $column_7_s_,  $column_8_s_,  $column_9_s_,
                $column_10_s_, $column_11_s_, $column_12_s_,
                $column_13_s_, $column_14_s_, $column_15_s_);

    $html = str_ireplace('class="clsRow"', 'class="clsSumRow"', $html);

    $this->summary_row = $html;
} /* set_summary_row_ */


public function  set_links(                                                /*F*/
    $new_href_s_    = null,
    $edit_href_s_   = null,
    $delete_href_s_ = null) {
    if ($new_href_s_ != = null) {
        $this->href_new = $new_href_s_;
    }

    if ($edit_href_s_ != = null) {
        $this->href_edit = $edit_href_s_;
    }

    if ($delete_href_s_ != = null) {
        $this->href_delete = $delete_href_s_;
    }
} /* set_links */


public function addColumn_($heading_s_, $data_type_s_, $field_name_s_) {
    array_push($this->headings, $heading_s_);
    array_push($this->data_types, $data_type_s_);
    array_push($this->field_names, $field_name_s_);
} /* addColumn_ */


public function echo($pdo_, $sql_s_) {
    echo '<div class="clsAllRowList" id="idDivRowList">'
    '<table class="clsAllRowList" id="idTableRowList" cellspacing="0">';

    /* assign a class name to every column */
    $classes = array();
    for ($col = 0, $iMax = count($this->headings) - 1; $col <= $iMax;
         $col++) {
        $head = $this->headings[$col];
        if ($head != '') {
            $class = '';
            if (strpos($head, '{') != = false) {
                $class = T_get_tag($head, '{class:', '}');
                if ($class != '') {
                    $head = T_remove_tag($head, '{class:', '}');
                }
            }

            if ($class == '') {
                $class = 'cls' . ($col + 1);
            }

            $this->headings[$col] = $head;
            array_push($classes, $class);
        }
    }

    /* output table headings */
    $echo = '<thead><tr>';
    for ($col = 0, $iMax = count($this->headings) - 1; $col <= $iMax;
         $col++) {
        $echo . = '<th class="' . $classes[$col] . '">' . App_label
                  ($this->headings[$col] . '{TH}') . '</th>';
    }
    $echo . = '</tr></thead>';
    echo $echo;

    /* output template row */
    echo '<tbody>';
    if ($this->fIncludeTemplateRow_) {

        $echo = '<tr class="clsRow" id="idTrTemplate" style="display:none">';
        for ($col = 0, $iMax = count($this->field_names) - 1; $col <= $iMax;
             $col++) {
            $class = $classes[$col];
            if ($this->href_edit != '' || $this->href_delete != '') {
                $link = ($class == 'clsDel' ||
                         $class == 'clsTog') ? $this->href_delete
                        : $this->href_edit;
                $link = $_link($link, '-');
                $echo . = "<td class=\"$class\">$link</td>";
            } else {
                $echo . = "<td class=\"$class\">$-</td>";
            }
        }
        $echo . = '</tr>';
        echo $echo;
    }

    /* output 'new record' row */
    $echo = '<tr class="clsRow" id="0">';
    for ($col = 0, $iMax = count($this->headings) - 1; $col <= $iMax;
         $col++) {
        $class = $classes[$col];
        if ($class == 'clsDel' || $class == 'clsTog') {
            $class = '';
        } else {
            $class = "class=\"$class\"";
        }

        $label = ($col == 0 ? App_label('create{}') : '...');

        if ($this->href_new != '') {
            $link = $_link($this->href_new, $label);
            $echo . = "<td $class>$link</td>";
        } else {
            $echo . = "<td $class>$label</td>";
        }
    }
    $echo . = '</tr>';
    echo $echo;

    /* output all rows returned by given sql statement */
    try {
        foreach ($pdo_->query($sql_s_) as $row) {
            $key_id = rawurlencode(strval($row[$this->key_field]));
            $echo = "<tr class=\"clsRow\" id=\"$key_id\">";

            for ($iField = 0, $iMax = count($this->field_names) - 1;
                 $iField <= $iMax; $iField++) {

                $field_name = $this->field_names[$iField];

                if (substr(strval($field_name), 0, 1) == '=') {
                    $val = substr(strval($field_name), 1);
                } else {
                    $val = $row[$field_name];
                    switch ($this->data_types[$iField]) {
                            CASE('date',     $val = read_date_($val);      );
                            CASE('datetime', $val = read_date_time_($val); );
                            CASE('int',      $val = read_int_($val);       );
                            CASE('money',    $val = read_money_($val);     );
                            CASE('text',     $val = read_text_($val);      );
                    }
                }

                $class = $classes[$iField];

                if ($this->href_edit != '' || $this->href_delete != '') {
                    $link = ($class == 'clsDel' ||
                             $class == 'clsTog') ? $this->href_delete
                            : $this->href_edit;
                    $link = str_ireplace('{id}', "$key_id", $link);
                    $link = $_link($link, $val);
                    $echo . = "<td class=\"$class\">$link</td>";
                } else {
                    $echo . = "<td class=\"$class\">$val</td>";
                }
            }
            $echo . = '</tr>';
            echo $echo;
        }
    } catch ( PDOException  $exception_ ) {
        log_exception_('#E1ED', 'PDO', $exception_->getMessage());
    } catch ( Exception  $exception_ ) {
        log_exception_('#E2FD', 'GEN', $exception_->getMessage());
    }

    if ($this->summary_row != '') {
        echo $this->summary_row;
    }

    echo '</tbody></table></div>';
} /* echo */


private function _link($href_s_, $content_s_) {
    if (substr($this->href_new, 0, 8) == 'onclick=') {
        $rv = html_link($this->fallback_href, $content_s_, '', $href_s_);
    } else {
        $rv = html_link($href_s_, $content_s_);
    }

    return $rv;
} /* _link */
#endif                                                                 /* 000 */
