#ifndef EMITTERACGT_H
#define EMITTERACGT_H

#include <QObject>

class emitterACGT : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief emitterACGT - Class who treat each sequence and have the expected result
    /// \param sequences - multimap containing pairs of sequences as String and it's expected result
    /// \param parent - QObject parent
    ///
    explicit emitterACGT(const std::multimap<std::string, bool> *sequences, QObject *parent = nullptr);
    ///
    /// \brief beginAnalysis - Begin analysis of the sequences
    ///
    void beginAnalysis();
    ///
    /// \brief getCurrentResult - Get the current expected result of the current sequences treatment
    /// \return The expected result of the sequence treated
    ///
    bool getCurrentResult();
private:
    ///
    /// \brief sequences - multimap storing the sequences and the corresponding result of each sequence
    ///
    const std::multimap<std::string, bool> *sequences;
    bool currentResult;
signals:
    ///
    /// \brief readA - signal who announce an A on the sequence
    ///
    void readA();
    ///
    /// \brief readC - signal who announce an C on the sequence
    ///
    void readC();
    ///
    /// \brief readG - signal who announce an G on the sequence
    ///
    void readG();
    ///
    /// \brief readT - signal who announce an T on the sequence
    ///
    void readT();
    ///
    /// \brief readX - signal who announce an X on the sequence
    ///
    void readX();
    ///
    /// \brief nextSequence - signal announcing that the next sequence will be treated (reset of the machines)
    ///
    void nextSequence();
    ///
    /// \brief finishedSequence - signal announcing a finished sequence (stop machines still running)
    ///
    void finishedSequence();
    ///
    /// \brief finished - signal announcing a finished analysis
    ///
    void finished();
};

#endif // EMITTERACGT_H
