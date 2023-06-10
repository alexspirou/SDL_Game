//The application time based timer
class CTimer
{
public:
    //Initializes variables
    CTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    unsigned int getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    unsigned int mStartTicks;

    //The ticks stored when the timer was paused
    unsigned int mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};