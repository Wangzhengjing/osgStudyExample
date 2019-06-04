#include "movemanipulator.h"

MoveManipulator::MoveManipulator()
{
}

btCollisionWorld* initCollision()
{
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher( collisionConfiguration );

    btVector3 worldAabbMin( -10000, -10000, -10000 );
    btVector3 worldAabbMax( 10000, 10000, 10000 );
    btBroadphaseInterface* inter = new btAxisSweep3( worldAabbMin, worldAabbMax, 1000 );

    btCollisionWorld* collisionWorld = new btCollisionWorld( dispatcher, inter, collisionConfiguration );

    return( collisionWorld );
}


osg::Node* createScene( btCollisionWorld* cw, MoveManipulator* mm, osg::ArgumentParser& arguments )
{
    osg::ref_ptr< osg::Group > root = new osg::Group;

    osg::Node* node = osgDB::readNodeFile("cow.osg");
    root->addChild(node);

    btCollisionObject* btBoxObject = new btCollisionObject;
    btBoxObject->setCollisionShape(osgbCollision::btTriMeshCollisionShapeFromOSG(node));
    btBoxObject->setCollisionFlags( btCollisionObject::CF_STATIC_OBJECT );
    cw->addCollisionObject( btBoxObject );

    // Create a box we can drag around with the mouse
    osg::Node* glider = osgDB::readNodeFile("glider.osg");
    osg::Matrix transMatrix = osg::Matrix::translate( 5., 0., 0. );
    osg::MatrixTransform* mt = new osg::MatrixTransform( transMatrix );
    mt->addChild(glider);
    root->addChild( mt );

    btBoxObject = new btCollisionObject;
    btBoxObject->setCollisionShape(osgbCollision::btBoxCollisionShapeFromOSG(glider));
    btBoxObject->setCollisionFlags( btCollisionObject::CF_KINEMATIC_OBJECT );
    btBoxObject->setWorldTransform( osgbCollision::asBtTransform( transMatrix ) );
    cw->addCollisionObject( btBoxObject );
    mm->setCollisionObject( btBoxObject );
    mm->setMatrixTransform( mt );

    return( root.release() );
}

void detectCollision( bool& lastColState, btCollisionWorld* cw )
{
    unsigned int numManifolds = cw->getDispatcher()->getNumManifolds();
    if( ( numManifolds == 0 ) && (lastColState == true ) )
    {
        osg::notify( osg::ALWAYS ) << "No collision." << std::endl;
        lastColState = false;
    }
    else {
        for( unsigned int i = 0; i < numManifolds; i++ )
        {
            btPersistentManifold* contactManifold = cw->getDispatcher()->getManifoldByIndexInternal(i);
            unsigned int numContacts = contactManifold->getNumContacts();
            for( unsigned int j=0; j<numContacts; j++ )
            {
                btManifoldPoint& pt = contactManifold->getContactPoint( j );
                if( ( pt.getDistance() <= 0.f ) && ( lastColState == false ) )
                {
                    // grab these values for the contact normal arrows:
                    osg::Vec3 pos = osgbCollision::asOsgVec3( pt.getPositionWorldOnA() );
                    osg::Vec3 normal = osgbCollision::asOsgVec3( pt.m_normalWorldOnB );
                    float pen = pt.getDistance(); //penetration depth

                    osg::Quat q;
                    q.makeRotate( osg::Vec3( 0, 0, 1 ), normal );

                    osg::notify( osg::ALWAYS ) << "Collision detected." << std::endl;

                    osg::notify( osg::ALWAYS ) << "\tPosition: " << pos << std::endl;
                    osg::notify( osg::ALWAYS ) << "\tNormal: " << normal << std::endl;
                    osg::notify( osg::ALWAYS ) << "\tPenetration depth: " << pen << std::endl;
                    lastColState = true;
                }
                else if( ( pt.getDistance() > 0.f ) && ( lastColState == true ) )
                {
                    osg::notify( osg::ALWAYS ) << "No collision." << std::endl;
                    lastColState = false;
                }
            }
        }
    }
}
