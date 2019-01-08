#include "cameramanipulator.h"

#include <osgEarth/Viewpoint>

using namespace osgEarth;

cameraManipulator::cameraManipulator()
{
}


//void
//cameraManipulator::setViewpoint(const Viewpoint& vp, double duration_seconds)
//{
//    // If the manip is not set up, save the viewpoint for later.
//    if ( !established() )
//    {
//        _pendingViewpoint = vp;
//        _pendingViewpointDuration.set(duration_seconds, Units::SECONDS);
//    }

//    else
//    {
//        // Save any existing tether node so we can properly invoke the callback.
//        osg::ref_ptr<osg::Node> oldEndNode;
//        if ( isTethering() && _tetherCallback.valid() )
//            _setVP1->getNode(oldEndNode);

//        // starting viewpoint; all fields will be set:
//        _setVP0 = getViewpoint();

//        // ending viewpoint
//        _setVP1 = vp;

//        // Reset the tethering offset quat.
//        _tetherRotationVP0 = _tetherRotation;
//        _tetherRotationVP1 = osg::Quat();

//        // Fill in any missing end-point data with defaults matching the current camera setup.
//        // Then all fields are guaranteed to contain usable data during transition.
//        double defPitch, defAzim;
//        getEulerAngles( _rotation, &defAzim, &defPitch );

//        if ( !_setVP1->heading().isSet() )
//            _setVP1->heading() = Angle(defAzim, Units::RADIANS);

//        if ( !_setVP1->pitch().isSet() )
//            _setVP1->pitch() = Angle(defPitch, Units::RADIANS);

//        if ( !_setVP1->range().isSet() )
//            _setVP1->range() = Distance(_distance, Units::METERS);

//        if ( !_setVP1->nodeIsSet() && !_setVP1->focalPoint().isSet() )
//        {
//            osg::ref_ptr<osg::Node> safeNode;
//            if ( _setVP0->getNode( safeNode ) )
//                _setVP1->setNode( safeNode.get() );
//            else
//                _setVP1->focalPoint() = _setVP0->focalPoint().get();
//        }

//        _setVPDuration.set( std::max(duration_seconds, 0.0), Units::SECONDS );

//        OE_DEBUG << LC << "setViewpoint:\n"
//            << "    from " << _setVP0->toString() << "\n"
//            << "    to   " << _setVP1->toString() << "\n";

//        // access the new tether node if it exists:
//        osg::ref_ptr<osg::Node> endNode;
//        _setVP1->getNode(endNode);

//        // Timed transition, we need to calculate some things:
//        if ( duration_seconds > 0.0 )
//        {
//            // Start point is the current manipulator center:
//            osg::Vec3d startWorld;
//            osg::ref_ptr<osg::Node> startNode;
//            startWorld = _setVP0->getNode(startNode) ? computeWorld(startNode.get()) : _center;

//            _setVPStartTime.unset();

//            // End point is the world coordinates of the target viewpoint:
//            osg::Vec3d endWorld;
//            if ( endNode.valid() )
//                endWorld = computeWorld(endNode.get());
//            else
//                _setVP1->focalPoint()->transform( _srs.get() ).toWorld(endWorld);

//            // calculate an acceleration factor based on the Z differential.
//            _setVPArcHeight = 0.0;
//            double range0 = _setVP0->range()->as(Units::METERS);
//            double range1 = _setVP1->range()->as(Units::METERS);

//            double pitch0 = _setVP0->pitch()->as(Units::RADIANS);
//            double pitch1 = _setVP1->pitch()->as(Units::RADIANS);

//            double h0 = range0 * sin( -pitch0 );
//            double h1 = range1 * sin( -pitch1 );
//            double dh = (h1 - h0);

//            // calculate the total distance the focal point will travel and derive an arc height:
//            double de = (endWorld - startWorld).length();

//            // maximum height during viewpoint transition
//            if ( _settings->getArcViewpointTransitions() )
//            {
//                _setVPArcHeight = osg::maximum( de - fabs(dh), 0.0 );
//            }

//            // calculate acceleration coefficients
//            if ( _setVPArcHeight > 0.0 )
//            {
//                // if we're arcing, we need seperate coefficients for the up and down stages
//                double h_apex = 2.0*(h0+h1) + _setVPArcHeight;
//                double dh2_up = fabs(h_apex - h0)/100000.0;
//                _setVPAccel = log10( dh2_up );
//                double dh2_down = fabs(h_apex - h1)/100000.0;
//                _setVPAccel2 = -log10( dh2_down );
//            }
//            else
//            {
//                // on arc => simple unidirectional acceleration:
//                double dh2 = (h1 - h0)/100000.0;
//                _setVPAccel = fabs(dh2) <= 1.0? 0.0 : dh2 > 0.0? log10( dh2 ) : -log10( -dh2 );
//                if ( fabs( _setVPAccel ) < 1.0 ) _setVPAccel = 0.0;
//            }

//            // Adjust the duration if necessary.
//            if ( _settings->getAutoViewpointDurationEnabled() )
//            {
//                double maxDistance = _srs->getEllipsoid()->getRadiusEquator();
//                double ratio = osg::clampBetween( de/maxDistance, 0.0, 1.0 );
//                ratio = accelerationInterp( ratio, -4.5 );
//                double minDur, maxDur;
//                _settings->getAutoViewpointDurationLimits( minDur, maxDur );
//                _setVPDuration.set( minDur + ratio*(maxDur-minDur), Units::SECONDS );
//            }
//        }

//        else
//        {
//            // Immediate transition? Just do it now.
//            _setVPStartTime->set( _time_s_now, Units::SECONDS );
//            setViewpointFrame( _time_s_now );
//        }

//        // Fire a tether callback if required.
//        if ( _tetherCallback.valid() )
//        {
//            // starting a tether to a NEW node:
//            if ( isTethering() && oldEndNode.get() != endNode.get() )
//                (*_tetherCallback)( endNode.get() );

//            // breaking a tether:
//            else if ( !isTethering() && oldEndNode.valid() )
//                (*_tetherCallback)( 0L );
//        }
//    }

//    // reset other global state flags.
//    _thrown      = false;
//    _task->_type = TASK_NONE;
//}
