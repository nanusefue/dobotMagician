
var bones = [];

var shoulder = new THREE.Bone();
var elbow = new THREE.Bone();
var hand = new THREE.Bone();

shoulder.add( elbow );
elbow.add( hand );

bones.push( shoulder );
bones.push( elbow );
bones.push( hand );

shoulder.position.y = -5;
elbow.position.y = 0;
hand.position.y = 5;

var armSkeleton = new THREE.Skeleton( bones );