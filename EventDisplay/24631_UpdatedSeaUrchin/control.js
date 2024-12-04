var Renderer;
var Scene;
var Camera;
var CanvasLeft, CanvasWidth;
var ParticleList = [];
var ParticleMaterials = [];
var ParticleGeometries = [];
var ParticleMeshes = [];
var InactiveParticleList = [];
var InactiveParticleMaterials = [];
var InactiveParticleGeometries = [];
var InactiveParticleMeshes = [];
var CameraSetting = {"X": 1.923282220535604, "Y": 1.9918518338681108, "Z": -1.1547778020415365, "UX": -0.6519199608248383, "UY": 0.7357836626326013, "UZ": 0.18336511795075847, "Step": 0.015, "ZoomStep": 1.10, "MinDistance": 3, "MaxDistance": 500, "MouseScale": 0.1};
var DefaultCameraSetting = {"X": 1.923282220535604, "Y": 1.9918518338681108, "Z": -1.1547778020415365, "UX": -0.6519199608248383, "UY": 0.7357836626326013, "UZ": 0.18336511795075847, "Step": 0.015, "ZoomStep": 1.10, "MinDistance": 3, "MaxDistance": 500, "MouseScale": 0.1};
var DefaultSetting = {"ParticleWidth": 0.05, "ParticleWidthBase": 0.02, "ParticleWidthReference": 5};
var PressedKeys = {Left: false, Right: false, Up: false, Down: false, RLeft: false, RRight: false, ZoomIn: false, ZoomOut: false, MouseLeft: false, MouseRight: false, Shift: false, Touch: false};
var MouseLocation = {"X": 0, "Y": 0, "DownX": 0, "DownY": 0};
var CameraZoomProposal = 1;
var Colors = ['3498DB', '9B59B6', 'D35400', '27AE60', '2C3E50', '1ABC9C'];
// var HighlightColors = ['FFFFFF', 'FFFFFF', 'FFFFFF', 'FFFFFF', 'FFFFFF', 'FFFFFF'];
var HighlightColors = ['FFB6C1', 'FFB6C1', 'FFB6C1', 'FFB6C1', 'FFB6C1', 'FFB6C1'];
var InactiveColors = ['FFFFFF', 'FF10F0', '0000FF', 'FFFFFF', 'FFFFFF'];
var MouseDetectionTolerance = 7;   // Tolerance in terms of pixels
var RayCaster;
var MaxJet = 4;
var DisableMouseObject = false;

function ParseParticles()
{
   ParticleList = [];
   InactiveParticleList = [];

   // these are the default!
   // ParticleList.push([Math.random() * 10 - 5, Math.random() * 10 - 5, Math.random() * 10 - 5, 5]);

   // Actual parsing
   var Lines = $('#ParticleInput').val().split('\n');
   for(var i = 0; i < Lines.length; i++)
   {
      if(Lines[i].includes('#'))
         continue;

      var Numbers = Lines[i].trim().split(/[ ,]+/);
      if(Numbers.length == 3)
         Numbers.push(1);
      if(Numbers.length != 4)
         continue;

      if(Numbers[3] < 0)
         InactiveParticleList.push(Numbers);
      else
         ParticleList.push(Numbers);
   }
}

function ConstructSceneElements()
{
   const Geometry = new THREE.SphereGeometry(0.1, 32, 32);
   const Material = new THREE.MeshBasicMaterial({color: 0xffff00});
   const Sphere = new THREE.Mesh(Geometry, Material);
   Sphere.scale.set(0.5, 0.5, 0.5);
   Scene.add(Sphere);
   
   const MaterialX = new THREE.MeshBasicMaterial({color: 0xAA0000});
   const MaterialY = new THREE.MeshBasicMaterial({color: 0x00AA00});
   const MaterialZ = new THREE.MeshBasicMaterial({color: 0x0000CC});
   const MaterialNX = new THREE.MeshBasicMaterial({color: 0x440000});
   const MaterialNY = new THREE.MeshBasicMaterial({color: 0x004400});
   const MaterialNZ = new THREE.MeshBasicMaterial({color: 0x000077});

   var Dist = [1, 5, 10, 25, 100];
   var Size = [1, 1.5, 2, 3, 6];

   /*
   for(var i = 0; i < Dist.length; i++)
   {
      const SphereX = new THREE.Mesh(Geometry, MaterialX);
      const SphereY = new THREE.Mesh(Geometry, MaterialY);
      const SphereZ = new THREE.Mesh(Geometry, MaterialZ);
      const SphereNX = new THREE.Mesh(Geometry, MaterialNX);
      const SphereNY = new THREE.Mesh(Geometry, MaterialNY);
      const SphereNZ = new THREE.Mesh(Geometry, MaterialNZ);

      SphereX.position.x = Dist[i];
      SphereY.position.y = Dist[i];
      SphereZ.position.z = Dist[i];
      SphereNX.position.x = -Dist[i];
      SphereNY.position.y = -Dist[i];
      SphereNZ.position.z = -Dist[i];

      SphereX.scale.set(Size[i], Size[i], Size[i]);
      SphereY.scale.set(Size[i], Size[i], Size[i]);
      SphereZ.scale.set(Size[i], Size[i], Size[i]);
      SphereNX.scale.set(Size[i], Size[i], Size[i]);
      SphereNY.scale.set(Size[i], Size[i], Size[i]);
      SphereNZ.scale.set(Size[i], Size[i], Size[i]);

      Scene.add(SphereX);
      Scene.add(SphereY);
      Scene.add(SphereZ);
      Scene.add(SphereNX);
      Scene.add(SphereNY);
      Scene.add(SphereNZ);
   }
   */

   const LineMaterialX = new THREE.LineBasicMaterial({color: 0xff0000});
   const LineMaterialY = new THREE.LineBasicMaterial({color: 0x00ff00});
   const LineMaterialZ = new THREE.LineBasicMaterial({color: 0x0000ff});

   const PointsX = [new THREE.Vector3(-1000, 0, 0), new THREE.Vector3(1000, 0, 0)];
   const PointsY = [new THREE.Vector3(0, -1000, 0), new THREE.Vector3(0, 1000, 0)];
   const PointsZ = [new THREE.Vector3(0, 0, -1000), new THREE.Vector3(0, 0, 1000)];

   const GeometryX = new THREE.BufferGeometry().setFromPoints(PointsX);
   const GeometryY = new THREE.BufferGeometry().setFromPoints(PointsY);
   const GeometryZ = new THREE.BufferGeometry().setFromPoints(PointsZ);

   const LineX = new THREE.Line(GeometryX, LineMaterialX);
   const LineY = new THREE.Line(GeometryY, LineMaterialY);
   const LineZ = new THREE.Line(GeometryZ, LineMaterialZ);

   // Scene.add(LineX);
   // Scene.add(LineY);
   // Scene.add(LineZ);
}

function ConstructParticles()
{
   for(var i = 0; i < ParticleList.length; i++)
   {
      var X = parseFloat(ParticleList[i][0]);
      var Y = parseFloat(ParticleList[i][1]);
      var Z = parseFloat(ParticleList[i][2]);
      var ID = parseFloat(ParticleList[i][3]);

      var L = Math.sqrt(X * X + Y * Y + Z * Z);

      const Points = [];
      Points.push(new THREE.Vector3(0, 0, 0));
      Points.push(new THREE.Vector3(X, Y, Z));

      var MaterialIndex = ID - 1;
      if(ID >= Colors.length)
         MaterialIndex = Colors.length - 1;

      var Tip = DefaultSetting.ParticleWidthBase + (DefaultSetting.ParticleWidth - DefaultSetting.ParticleWidthBase) / DefaultSetting.ParticleWidthReference * L;

      const Material = new THREE.MeshBasicMaterial({color: parseInt('0x' + Colors[MaterialIndex])});
      const Geometry = new THREE.CylinderGeometry(Tip, DefaultSetting.ParticleWidthBase, L, 32, 1, false);
      const Cylinder = new THREE.Mesh(Geometry, Material);
      
      Cylinder.translateX(X / 2);
      Cylinder.translateY(Y / 2);
      Cylinder.translateZ(Z / 2);

      if(X != 0 || Z != 0)
      {
         const V1 = new THREE.Vector3(0, 1, 0);
         const V2 = new THREE.Vector3(X, Y, Z);

         const Angle = V1.angleTo(V2);

         const Axis = new THREE.Vector3(1, 1, 1);
         Axis.crossVectors(V1, V2);

         var RotationObjectMatrix = new THREE.Matrix4();
         RotationObjectMatrix.makeRotationAxis(Axis.normalize(), Angle);
         Cylinder.matrix.multiply(RotationObjectMatrix);
         Cylinder.rotation.setFromRotationMatrix(Cylinder.matrix);
      }

      // Cylinder.position.x = X / 2;
      // Cylinder.position.y = Y / 2;
      // Cylinder.position.z = Z / 2;

      Scene.add(Cylinder);

      ParticleMaterials.push(Material);
      ParticleGeometries.push(Geometry);
      ParticleMeshes.push(Cylinder);
   }

   for(var i = 0; i < InactiveParticleList.length; i++)
   {
      var X = parseFloat(InactiveParticleList[i][0]);
      var Y = parseFloat(InactiveParticleList[i][1]);
      var Z = parseFloat(InactiveParticleList[i][2]);
      var ID = parseFloat(InactiveParticleList[i][3]);

      var L = Math.sqrt(X * X + Y * Y + Z * Z);

      const Points = [];
      Points.push(new THREE.Vector3(0, 0, 0));
      Points.push(new THREE.Vector3(X, Y, Z));

      var Tip = DefaultSetting.ParticleWidthBase + (DefaultSetting.ParticleWidth - DefaultSetting.ParticleWidthBase) / DefaultSetting.ParticleWidthReference * L;

      // const Material     = new THREE.LineBasicMaterial({color: 0x0000ff});
      // const Geometry     = new THREE.BufferGeometry().setFromPoints(Points);
      // const Line         = new THREE.Line(Geometry, Material);
      
      const Material = new THREE.MeshBasicMaterial({color: parseInt('0x' + InactiveColors[0])});
      const Geometry = new THREE.CylinderGeometry(Tip, DefaultSetting.ParticleWidthBase * 0.25, L, 32, 1, false);
      const Cylinder = new THREE.Mesh(Geometry, Material);
      
      Cylinder.translateX(X / 2);
      Cylinder.translateY(Y / 2);
      Cylinder.translateZ(Z / 2);

      if(X != 0 || Z != 0)
      {
         const V1 = new THREE.Vector3(0, 1, 0);
         const V2 = new THREE.Vector3(X, Y, Z);

         const Angle = V1.angleTo(V2);

         const Axis = new THREE.Vector3(1, 1, 1);
         Axis.crossVectors(V1, V2);

         var RotationObjectMatrix = new THREE.Matrix4();
         RotationObjectMatrix.makeRotationAxis(Axis.normalize(), Angle);
         Cylinder.matrix.multiply(RotationObjectMatrix);
         Cylinder.rotation.setFromRotationMatrix(Cylinder.matrix);
      }

      // Scene.add(Line);
      Scene.add(Cylinder);

      InactiveParticleMaterials.push(Material);
      InactiveParticleGeometries.push(Geometry);
      // InactiveParticleMeshes.push(Line);
      InactiveParticleMeshes.push(Cylinder);
   }
}

function UpdateCamera()
{
   Camera.position.set(CameraSetting.X, CameraSetting.Y, CameraSetting.Z);
   Camera.up.set(CameraSetting.UX, CameraSetting.UY, CameraSetting.UZ);
   Camera.lookAt(0, 0, 0);
   Camera.updateMatrixWorld();
}

function Animate()
{
   requestAnimationFrame(Animate);

   var C = new THREE.Vector3(CameraSetting.X, CameraSetting.Y, CameraSetting.Z);
   var U = new THREE.Vector3(CameraSetting.UX, CameraSetting.UY, CameraSetting.UZ);
   var L = new THREE.Vector3(0, 0, 0);
   L.crossVectors(C, U).normalize();

   var CSize = C.length();

   if(PressedKeys.Up == true)
   {
      C.sub(U.multiplyScalar(parseFloat(CameraSetting.Step) * CSize));
      U.crossVectors(L, C).normalize();
   }
   if(PressedKeys.Down == true)
   {
      C.add(U.multiplyScalar(parseFloat(CameraSetting.Step) * CSize));
      U.crossVectors(L, C).normalize();
   }
   if(PressedKeys.Left == true)
      C.sub(L.normalize().multiplyScalar(parseFloat(CameraSetting.Step) * CSize));
   if(PressedKeys.Right == true)
      C.add(L.normalize().multiplyScalar(parseFloat(CameraSetting.Step) * CSize));

   if(PressedKeys.MouseLeft == true)
   {
      var DeltaX = -(MouseLocation.X - MouseLocation.DownX) * CameraSetting.MouseScale;
      var DeltaY = -(MouseLocation.Y - MouseLocation.DownY) * CameraSetting.MouseScale;

      C.sub(U.multiplyScalar(DeltaY * parseFloat(CameraSetting.Step) * CSize));
      U.crossVectors(L, C).normalize();
      C.sub(L.normalize().multiplyScalar(DeltaX * parseFloat(CameraSetting.Step) * CSize));

      MouseLocation.DownX = MouseLocation.X;
      MouseLocation.DownY = MouseLocation.Y;
   }

   if(PressedKeys.ZoomIn == true)
      CSize = CSize / CameraSetting.ZoomStep;
   if(PressedKeys.ZoomOut == true)
      CSize = CSize * CameraSetting.ZoomStep;
   CSize = CSize * CameraZoomProposal;
   CameraZoomProposal = 1;

   if(CSize < CameraSetting.MinDistance)
      CSize = CameraSetting.MinDistance;
   if(CSize > CameraSetting.MaxDistance)
      CSize = CameraSetting.MaxDistance;

   C.normalize().multiplyScalar(CSize);

   if(PressedKeys.RLeft == true)
      U.sub(L.normalize().multiplyScalar(parseFloat(CameraSetting.Step))).normalize();
   if(PressedKeys.RRight == true)
      U.add(L.normalize().multiplyScalar(parseFloat(CameraSetting.Step))).normalize();
   
   CameraSetting.X = C.x;
   CameraSetting.Y = C.y;
   CameraSetting.Z = C.z;
   CameraSetting.UX = U.x;
   CameraSetting.UY = U.y;
   CameraSetting.UZ = U.z;

   UpdateCamera();

   DetectMouseObject();

   Renderer.render(Scene, Camera);
}

function DetectMouseObject()
{
   if(DisableMouseObject == true)
      return;

   if(ParticleMeshes.length == 0)
      return;

   var PointA = new THREE.Vector3(0, 0, 0);
   PointA.project(Camera);
   var AX = (PointA.x + 1) / 2 * CanvasWidth;
   var AY = -(PointA.y - 1) / 2 * CanvasHeight;

   var MX = MouseLocation.X - AX;
   var MY = MouseLocation.Y - AY;
   var M = Math.sqrt(MX * MX + MY * MY);
      
   var BestIndex = -1, BestDistance = -1;
   for(var i = 0; i < ParticleList.length; i++)
   {
      var PointB = new THREE.Vector3(ParticleList[i][0], ParticleList[i][1], ParticleList[i][2]);
      PointB.project(Camera);
      var BX = (PointB.x + 1) / 2 * CanvasWidth - AX;
      var BY = -(PointB.y - 1) / 2 * CanvasHeight - AY;
      var B = Math.sqrt(BX * BX + BY * BY);

      var T = (BX * MX + BY * MY) / B;
      if(T < 0 || T > B)
         continue;

      var D = Math.sqrt(M * M - T * T);

      if(BestDistance < 0 || BestDistance > D)
      {
         BestIndex = i;
         BestDistance = D;
      }
   }

   for(var i = 0; i < ParticleList.length; i++)
   {
      var MaterialIndex = ParticleList[i][3] - 1;
      if(MaterialIndex >= Colors.length)
         MaterialIndex = Colors.length - 1;
      ParticleMaterials[i].color.set(parseInt('0x' + Colors[MaterialIndex]));
   }

   if(BestDistance > MouseDetectionTolerance || BestIndex < 0)
   {
      $('#ParticleOverlay').html('Created by Yi Chen');
      $('#ParticleOverlay').show();
   }
   else
   {
      var ParticleString = "";

      var X = parseFloat(ParticleList[BestIndex][0]);
      var Y = parseFloat(ParticleList[BestIndex][1]);
      var Z = parseFloat(ParticleList[BestIndex][2]);
      var T = parseFloat(Math.sqrt(X * X + Y * Y));
      var L = parseFloat(Math.sqrt(X * X + Y * Y + Z * Z));
      var Theta = parseFloat(Math.acos(Z / L));
      var Eta = parseFloat(Math.log((L + Z) / (L - Z)) / 2);
      var Phi = parseFloat(Math.acos(X / T));
      if(Y < 0)
         Phi = -Phi;

      ParticleString = ParticleString + "P = (" + X.toFixed(2) + ", " + Y.toFixed(2) + ", " + Z.toFixed(2) + ") GeV, ";
      ParticleString = ParticleString + "|P| = " + L.toFixed(2) + " GeV, ";
      ParticleString = ParticleString + "(P<sub>T</sub>, &theta;, &eta;, &phi;) = (" + T.toFixed(2) + " GeV, " + Theta.toFixed(3) + ", " + Eta.toFixed(3) + ", " + Phi.toFixed(3) + "), ";
      ParticleString = ParticleString + "ID = " + ParticleList[BestIndex][3];
      
      ParticleMaterials[BestIndex].color.set(parseInt('0x' + HighlightColors[MaterialIndex]));

      $('#ParticleOverlay').html(ParticleString);
      $('#ParticleOverlay').show();
   }
}

function DetectMouseObjectRay()
{
   if(ParticleMeshes.length == 0)
      return;

   var Mouse2 = new THREE.Vector2();
   Mouse2.x = MouseLocation.X / CanvasWidth * 2 - 1;
   Mouse2.y = -MouseLocation.Y / CanvasHeight * 2 + 1;

   RayCaster.setFromCamera(Mouse2, Camera);

   const Intersects = RayCaster.intersectObjects(ParticleMeshes);

   if(Intersects.length > 0)
      console.log(Intersects);

   if(Intersects.length == 0)
      $('#ParticleOverlay').hide();
   else
   {
      var ParticleString = "";

      for(var i = 0; i < ParticleList.length; i++)
      {
         if(ParticleMeshes[i] == Intersects[0])
         {
            var X = ParticleList[i][0];
            var Y = ParticleList[i][1];
            var Z = ParticleList[i][2];
            var L = Math.sqrt(X * X + Y * Y + Z * Z);

            ParticleString = ParticleString + "P = (" + X + ", " + Y + ", " + Z + "), ";
            ParticleString = ParticleString + "|P| = " + L + ", ";
            ParticleString = ParticleString + "ID = " + ParticleList[i][3];
         }
      }

      $('#ParticleOverlay').html(ParticleString);
      $('#ParticleOverlay').show();
   }
}

function KeySwitchHandler(Key, Value)
{
   switch(Key.which)
   {
      case 37: // left
         PressedKeys.Left = Value;
         break;
      case 38: // up
         PressedKeys.Up = Value;
         break;
      case 39: // right
         PressedKeys.Right = Value;
         break;
      case 40: // down
         PressedKeys.Down = Value;
         break;
      case 33: // Page up
         PressedKeys.RLeft = Value;
         break;
      case 34: // Page down
         PressedKeys.RRight = Value;
         break;
      case 36: // Home
         PressedKeys.ZoomIn = Value;
         break;
      case 35: // End
         PressedKeys.ZoomOut = Value;
         break;
      case 65: // A
         PressedKeys.Left = Value;
         break;
      case 68: // D
         PressedKeys.Right = Value;
         break;
      case 83: // S
         PressedKeys.Down = Value;
         break;
      case 87: // W
         PressedKeys.Up = Value;
         break;
      case 81: // Q
         PressedKeys.RLeft = Value;
         break;
      case 69: // E
         PressedKeys.RRight = Value;
         break;
      case 82: // R
         PressedKeys.ZoomIn = Value;
         break;
      case 70: // F
         PressedKeys.ZoomOut = Value;
         break;
      case 16: // shift
         PressedKeys.Shift = Value;
         break;
      default:
         console.log("Key " + Key.which + " typed or released!");
         return; // exit this handler for other keys
   }
         
   Key.preventDefault(); // prevent the default action (scroll / move caret)
}

function MouseDownHandler(Event)
{
   MouseLocation.DownX = Event.clientX - CanvasLeft;
   MouseLocation.DownY = Event.clientY - CanvasTop;

   switch(Event.button)
   {
      case 0:   // left button
         PressedKeys.MouseLeft = true;
         break;
      default:
         console.log(Event.button);
         break;
   }
}

function MouseMoveHandler(Event)
{
   MouseLocation.X = Event.clientX - CanvasLeft;
   MouseLocation.Y = Event.clientY - CanvasTop;
}

function MouseUpHandler(Event)
{
   switch(Event.button)
   {
      case 0:   // left button
         PressedKeys.MouseLeft = false;
         break;
      default:
         console.log(Event.button);
         return;
   }
}

function MouseWheelHandler(Event)
{
   if(Event.originalEvent.deltaY < 0)
      CameraZoomProposal = CameraZoomProposal / CameraSetting.ZoomStep;
   else
      CameraZoomProposal = CameraZoomProposal * CameraSetting.ZoomStep;
}

function ResetParticles()
{
   // kill current particles and inactive particles
   for(var i = 0; i < ParticleMeshes.length; i++)
      Scene.remove(ParticleMeshes[i]);
   for(var i = 0; i < ParticleGeometries.length; i++)
      ParticleGeometries[i].dispose();
   for(var i = 0; i < ParticleMaterials.length; i++)
      ParticleMaterials[i].dispose();
   ParticleMeshes = [];
   ParticleGeometries = [];
   ParticleMaterials = [];

   for(var i = 0; i < InactiveParticleMeshes.length; i++)
      Scene.remove(InactiveParticleMeshes[i]);
   for(var i = 0; i < InactiveParticleGeometries.length; i++)
      InactiveParticleGeometries[i].dispose();
   for(var i = 0; i < InactiveParticleMaterials.length; i++)
      InactiveParticleMaterials[i].dispose();
   InactiveParticleMeshes = [];
   InactiveParticleGeometries = [];
   InactiveParticleMaterials = [];

   // Read in new particles
   ParseParticles();

   // Construct particles in the scene
   ConstructParticles();

   // Update also the extra information
   $('#QuickTipOverlay').html($('#ExtraInformation').val());
}

function Initialize()
{
   console.log("Initializing :D");

   CanvasWidth = $('#DisplayDiv').width();
   CanvasHeight = $('#DisplayDiv').height();
   CanvasLeft = $('#DisplayDiv').offset().left;
   CanvasTop = $('#DisplayDiv').offset().top;

   Renderer = new THREE.WebGLRenderer();
   Renderer.setSize(CanvasWidth, CanvasHeight);
   Container = document.getElementById('DisplayDiv');
   Container.appendChild(Renderer.domElement);

   Scene = new THREE.Scene();
   Camera = new THREE.PerspectiveCamera(60, CanvasWidth / CanvasHeight, 1, 1000);
   // Camera = new THREE.OrthographicCamera(-5, 5, -5, 5, 1, 1000);

   ParseParticles();
   ConstructSceneElements();
   ConstructParticles();

   Camera.position.x = CameraSetting.X;
   Camera.position.y = CameraSetting.Y;
   Camera.position.z = CameraSetting.Z;
   Camera.lookAt(0, 0, 0);
   Camera.up.set(CameraSetting.UX, CameraSetting.UY, CameraSetting.UZ);

   RayCaster = new THREE.Raycaster();

   Animate();

   $('#DisplayDiv').on('keydown', function(Key) {KeySwitchHandler(Key, true);});
   $('#DisplayDiv').on('keyup', function(Key) {KeySwitchHandler(Key, false);});
   $('#DisplayDiv').on('mousedown', function(Event) {MouseDownHandler(Event);});
   $('#DisplayDiv').on('mousemove', function(Event) {MouseMoveHandler(Event);});
   $('#DisplayDiv').on('mouseup', function(Event) {MouseUpHandler(Event);});
   $('#DisplayDiv').on('wheel', function(Event){MouseWheelHandler(Event);});
   $('#ResetButton').click(function()
   {
      CameraSetting.X = DefaultCameraSetting.X;
      CameraSetting.Y = DefaultCameraSetting.Y;
      CameraSetting.Z = DefaultCameraSetting.Z;
      CameraSetting.UX = DefaultCameraSetting.UX;
      CameraSetting.UY = DefaultCameraSetting.UY;
      CameraSetting.UZ = DefaultCameraSetting.UZ;
   });
   $('#UpdateButton').click(function() {ResetParticles();});

   $(window).resize(function()
   {
      CanvasWidth = $('#DisplayDiv').width();
      CanvasHeight = $('#DisplayDiv').height();
      CanvasLeft = $('#DisplayDiv').offset().left;
      CanvasTop = $('#DisplayDiv').offset().top;

      Camera.aspect = CanvasWidth / CanvasHeight;
      Camera.updateProjectionMatrix();

      Renderer.setSize(CanvasWidth, CanvasHeight);
   });

   var ColorString = '';
   for(var i = 0; i < MaxJet; i++)
      ColorString = ColorString + ' <span style="color: #' + Colors[i] + ';">Jet ' + (i + 1) + '</span><br />';
   ColorString = ColorString + ' <span style="color: #' + InactiveColors[0] + ';">Thrust</span><br />';
   $('#ColorOverlay').html(ColorString);
   
   $('#QuickTipOverlay').html($('#ExtraInformation').val());
}

$(window).on('load', Initialize);

