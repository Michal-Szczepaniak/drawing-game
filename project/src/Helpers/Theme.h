#ifndef GRAPHIE_THEME_H
#define GRAPHIE_THEME_H

class Theme {
public:
    static Theme& getInstance()
    {
        static Theme instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    Theme(Theme const&) = delete;
    void operator=(Theme const&) = delete;


    float getPaddingLarge();
    float getPaddingMedium();
    float getPaddingSmall();

private:
    Theme();
};


#endif //GRAPHIE_THEME_H
