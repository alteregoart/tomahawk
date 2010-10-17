#include "tomahawk/query.h"

#include <QtAlgorithms>

using namespace Tomahawk;

void
Query::addResults( const QList< Tomahawk::result_ptr >& newresults )
{
    bool becameSolved = false;
    {
        QMutexLocker lock( &m_mut );
        m_results.append( newresults );
        qStableSort( m_results.begin(), m_results.end(), Query::resultSorter );

        // hook up signals, and check solved status
        foreach( const result_ptr& rp, newresults )
        {
            connect( rp.data(), SIGNAL( becomingUnavailable() ), SLOT( resultUnavailable() ) );
            if( !m_solved && rp->score() > 0.99 )
            {
                m_solved = true;
                becameSolved = true;
            }
        }
    }
    emit resultsAdded( newresults );
    if( becameSolved ) emit solvedStateChanged( true );
}


void
Query::resultUnavailable()
{
    Result* result = (Result*) sender();
    Q_ASSERT( result );

    for(int i = 0; i < m_results.length(); ++i )
    {
        if( m_results.value( i ).data() == result )
        {
            m_results.removeAt( i );
            break;
        }
    }
}


void
Query::removeResult( Tomahawk::result_ptr result )
{
    bool becameUnsolved = false;
    {
        QMutexLocker lock( &m_mut );
        m_results.removeAll( result );

        if ( m_results.isEmpty() )  // FIXME proper score checking
            becameUnsolved = true;

    }
    emit resultsRemoved( result );
    if( becameUnsolved ) emit solvedStateChanged( false );
}


QList< result_ptr >
Query::results() const
{
    QMutexLocker lock( &m_mut );
    return m_results;
}


unsigned int
Query::numResults() const
{
    QMutexLocker lock( &m_mut );
    return m_results.length();
}


QID Query::id() const
{
    if ( m_qid.isEmpty() )
    {
        m_qid = uuid();

        QVariantMap m = m_v.toMap();
        m.insert( "qid", m_qid );

        m_v = m;
    }
    return m_qid;
}


bool Query::resultSorter( const result_ptr& left, const result_ptr& right )
{
    return left->score() > right->score();
}

