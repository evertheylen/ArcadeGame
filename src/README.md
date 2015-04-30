
# ArcadeGame

Docs voor onze ArcadeGame.


## Entity

WIP :D

  * Physics
    * Solid
    * Small (for stuff that should have no real physical influence)
    * Container
  * Life
    * Immutable
    * SingleLife
  * InterActive
    * Nothing
    * Lethal
  * Printer
    * Standard
    * LifeBased
  * Soon... HTML?

Each provides the following:
  * Physics:
    * has an enum: (because stuff needs to react differently on different physics)
      * CONTAINER
      * SOLID
      * SMALL
    * bool collide(Entity*)
      * returns whether or not it has taken care of the object
    *