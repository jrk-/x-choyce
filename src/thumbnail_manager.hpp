#ifndef _THUMBNAIL_MANAGER_HPP
#define _THUMBNAIL_MANAGER_HPP

#include <vector>
#include <unordered_map>

#include "cyclic_iterator.hpp"
#include "layout_t.hpp"
#include "chooser_t.hpp"
#include "thumbnail_t.hpp"
#include "x_event_handler_t.hpp"
#include "x_connection.hpp"

class thumbnail_manager : public chooser_t
                        , public x_event_handler_t
{
  public:
    thumbnail_manager(x_connection &,
                      const layout_t *,
                      const thumbnail_t::factory *);

    ~thumbnail_manager(void);

    void show(void);
    void hide(void);
    void next(void);
    void prev(void);
    void east(void);
    void west(void);
    void north(void);
    void south(void);
    void select(const xcb_window_t & window = XCB_NONE);
    void highlight(const unsigned int & window = XCB_NONE);

    bool handle(xcb_generic_event_t *);

  private:
    typedef std::vector<xcb_window_t> window_list_t;
    typedef const_cyclic_iterator<window_list_t> window_cyclic_iterator;

    x_connection & _c;
    const layout_t * _layout;
    const thumbnail_t::factory * _factory;

    window_cyclic_iterator _cyclic_iterator;

    window_list_t _windows;
    std::unordered_map<xcb_window_t, thumbnail_t::ptr> _thumbnails;

    bool _active = false;
    xcb_window_t _next_window = XCB_NONE;
    xcb_window_t _current_window = XCB_NONE;

    void reset(void);
    void update(void);
    void next_or_prev(bool next);
    rectangle query_current_screen(void);

    bool is_east(double);
    bool is_west(double);
    bool is_north(double);
    bool is_south(double);
    xcb_window_t nearest_thumbnail(const std::function<bool(double)> &);
};

#endif