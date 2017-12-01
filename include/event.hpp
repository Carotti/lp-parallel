#ifndef EVENT_HPP
#define EVENT_HPP

class Event {
public:
    Event(double _logical_time, bool _null = false);

    double get_logical_time() const;

    virtual bool is_null() const;

    void print() const;

private:
    double logical_time;
    bool null;
};

#endif
