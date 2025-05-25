(define (problem minecraft-tower-3d-multi)
  (:domain minecraft)
  
  (:objects
    robot
    block1 block2 block3
    pos-0-0-0 pos-0-0-1 pos-0-0-2
    pos-0-1-0 pos-0-1-1 pos-0-1-2
    pos-0-2-0 pos-0-2-1 pos-0-2-2
    pos-1-0-0 pos-1-0-1 pos-1-0-2
    pos-1-1-0 pos-1-1-1 pos-1-1-2
    pos-1-2-0 pos-1-2-1 pos-1-2-2
    pos-2-0-0 pos-2-0-1 pos-2-0-2
    pos-2-1-0 pos-2-1-1 pos-2-1-2
    pos-2-2-0 pos-2-2-1 pos-2-2-2
  )
  
  (:init
    ; Define initial position of the robot
    (at-robot pos-0-0-0)
    (handempty)
    
    ; Define initial positions of blocks (all on the ground)
    (block-at block1 pos-1-0-0)
    (block-at block2 pos-2-0-0)
    (block-at block3 pos-2-1-0)
    
    ; Define which positions are on the ground (z=0)
    (ground-pos pos-0-0-0) (ground-pos pos-0-1-0) (ground-pos pos-0-2-0)
    (ground-pos pos-1-0-0) (ground-pos pos-1-1-0) (ground-pos pos-1-2-0)
    (ground-pos pos-2-0-0) (ground-pos pos-2-1-0) (ground-pos pos-2-2-0)
    
    ; Define which positions are free (no block or robot on them)
    ; The robot position is not free
    (free pos-0-1-0) (free pos-0-2-0)
    (free pos-1-1-0) (free pos-1-2-0)
    (free pos-2-2-0)
    
    ; All positions at z=1 and z=2 are free
    (free pos-0-0-1) (free pos-0-1-1) (free pos-0-2-1)
    (free pos-1-0-1) (free pos-1-1-1) (free pos-1-2-1)
    (free pos-2-0-1) (free pos-2-1-1) (free pos-2-2-1)
    
    (free pos-0-0-2) (free pos-0-1-2) (free pos-0-2-2)
    (free pos-1-0-2) (free pos-1-1-2) (free pos-1-2-2)
    (free pos-2-0-2) (free pos-2-1-2) (free pos-2-2-2)
    
    ; Define blocks that are clear (no blocks on top)
    (clear block1)
    (clear block2)
    (clear block3)
    
    ; Define which blocks are on the ground
    (on-ground block1)
    (on-ground block2)
    (on-ground block3)
    
    ; Define above relations (position at z+1 is above position at z)
    (above pos-0-0-1 pos-0-0-0) (above pos-0-1-1 pos-0-1-0) (above pos-0-2-1 pos-0-2-0)
    (above pos-1-0-1 pos-1-0-0) (above pos-1-1-1 pos-1-1-0) (above pos-1-2-1 pos-1-2-0)
    (above pos-2-0-1 pos-2-0-0) (above pos-2-1-1 pos-2-1-0) (above pos-2-2-1 pos-2-2-0)
    
    (above pos-0-0-2 pos-0-0-1) (above pos-0-1-2 pos-0-1-1) (above pos-0-2-2 pos-0-2-1)
    (above pos-1-0-2 pos-1-0-1) (above pos-1-1-2 pos-1-1-1) (above pos-1-2-2 pos-1-2-1)
    (above pos-2-0-2 pos-2-0-1) (above pos-2-1-2 pos-2-1-1) (above pos-2-2-2 pos-2-2-1)
    
    ; Define adjacency relations
    ; Ground level adjacencies (z=0)
    (adjacent pos-0-0-0 pos-0-1-0) (adjacent pos-0-0-0 pos-1-0-0) (adjacent pos-0-0-0 pos-0-0-1)
    (adjacent pos-0-1-0 pos-0-0-0) (adjacent pos-0-1-0 pos-0-2-0) (adjacent pos-0-1-0 pos-1-1-0) (adjacent pos-0-1-0 pos-0-1-1)
    (adjacent pos-0-2-0 pos-0-1-0) (adjacent pos-0-2-0 pos-1-2-0) (adjacent pos-0-2-0 pos-0-2-1)
    (adjacent pos-1-0-0 pos-0-0-0) (adjacent pos-1-0-0 pos-1-1-0) (adjacent pos-1-0-0 pos-2-0-0) (adjacent pos-1-0-0 pos-1-0-1)
    (adjacent pos-1-1-0 pos-0-1-0) (adjacent pos-1-1-0 pos-1-0-0) (adjacent pos-1-1-0 pos-1-2-0) (adjacent pos-1-1-0 pos-2-1-0) (adjacent pos-1-1-0 pos-1-1-1)
    (adjacent pos-1-2-0 pos-0-2-0) (adjacent pos-1-2-0 pos-1-1-0) (adjacent pos-1-2-0 pos-2-2-0) (adjacent pos-1-2-0 pos-1-2-1)
    (adjacent pos-2-0-0 pos-1-0-0) (adjacent pos-2-0-0 pos-2-1-0) (adjacent pos-2-0-0 pos-2-0-1)
    (adjacent pos-2-1-0 pos-1-1-0) (adjacent pos-2-1-0 pos-2-0-0) (adjacent pos-2-1-0 pos-2-2-0) (adjacent pos-2-1-0 pos-2-1-1)
    (adjacent pos-2-2-0 pos-1-2-0) (adjacent pos-2-2-0 pos-2-1-0) (adjacent pos-2-2-0 pos-2-2-1)
    
    ; First level adjacencies (z=1)
    (adjacent pos-0-0-1 pos-0-1-1) (adjacent pos-0-0-1 pos-1-0-1) (adjacent pos-0-0-1 pos-0-0-0) (adjacent pos-0-0-1 pos-0-0-2)
    (adjacent pos-0-1-1 pos-0-0-1) (adjacent pos-0-1-1 pos-0-2-1) (adjacent pos-0-1-1 pos-1-1-1) (adjacent pos-0-1-1 pos-0-1-0) (adjacent pos-0-1-1 pos-0-1-2)
    (adjacent pos-0-2-1 pos-0-1-1) (adjacent pos-0-2-1 pos-1-2-1) (adjacent pos-0-2-1 pos-0-2-0) (adjacent pos-0-2-1 pos-0-2-2)
    (adjacent pos-1-0-1 pos-0-0-1) (adjacent pos-1-0-1 pos-1-1-1) (adjacent pos-1-0-1 pos-2-0-1) (adjacent pos-1-0-1 pos-1-0-0) (adjacent pos-1-0-1 pos-1-0-2)
    (adjacent pos-1-1-1 pos-0-1-1) (adjacent pos-1-1-1 pos-1-0-1) (adjacent pos-1-1-1 pos-1-2-1) (adjacent pos-1-1-1 pos-2-1-1) (adjacent pos-1-1-1 pos-1-1-0) (adjacent pos-1-1-1 pos-1-1-2)
    (adjacent pos-1-2-1 pos-0-2-1) (adjacent pos-1-2-1 pos-1-1-1) (adjacent pos-1-2-1 pos-2-2-1) (adjacent pos-1-2-1 pos-1-2-0) (adjacent pos-1-2-1 pos-1-2-2)
    (adjacent pos-2-0-1 pos-1-0-1) (adjacent pos-2-0-1 pos-2-1-1) (adjacent pos-2-0-1 pos-2-0-0) (adjacent pos-2-0-1 pos-2-0-2)
    (adjacent pos-2-1-1 pos-1-1-1) (adjacent pos-2-1-1 pos-2-0-1) (adjacent pos-2-1-1 pos-2-2-1) (adjacent pos-2-1-1 pos-2-1-0) (adjacent pos-2-1-1 pos-2-1-2)
    (adjacent pos-2-2-1 pos-1-2-1) (adjacent pos-2-2-1 pos-2-1-1) (adjacent pos-2-2-1 pos-2-2-0) (adjacent pos-2-2-1 pos-2-2-2)
    
    ; Second level adjacencies (z=2)
    (adjacent pos-0-0-2 pos-0-1-2) (adjacent pos-0-0-2 pos-1-0-2) (adjacent pos-0-0-2 pos-0-0-1)
    (adjacent pos-0-1-2 pos-0-0-2) (adjacent pos-0-1-2 pos-0-2-2) (adjacent pos-0-1-2 pos-1-1-2) (adjacent pos-0-1-2 pos-0-1-1)
    (adjacent pos-0-2-2 pos-0-1-2) (adjacent pos-0-2-2 pos-1-2-2) (adjacent pos-0-2-2 pos-0-2-1)
    (adjacent pos-1-0-2 pos-0-0-2) (adjacent pos-1-0-2 pos-1-1-2) (adjacent pos-1-0-2 pos-2-0-2) (adjacent pos-1-0-2 pos-1-0-1)
    (adjacent pos-1-1-2 pos-0-1-2) (adjacent pos-1-1-2 pos-1-0-2) (adjacent pos-1-1-2 pos-1-2-2) (adjacent pos-1-1-2 pos-2-1-2) (adjacent pos-1-1-2 pos-1-1-1)
    (adjacent pos-1-2-2 pos-0-2-2) (adjacent pos-1-2-2 pos-1-1-2) (adjacent pos-1-2-2 pos-2-2-2) (adjacent pos-1-2-2 pos-1-2-1)
    (adjacent pos-2-0-2 pos-1-0-2) (adjacent pos-2-0-2 pos-2-1-2) (adjacent pos-2-0-2 pos-2-0-1)
    (adjacent pos-2-1-2 pos-1-1-2) (adjacent pos-2-1-2 pos-2-0-2) (adjacent pos-2-1-2 pos-2-2-2) (adjacent pos-2-1-2 pos-2-1-1)
    (adjacent pos-2-2-2 pos-1-2-2) (adjacent pos-2-2-2 pos-2-1-2) (adjacent pos-2-2-2 pos-2-2-1)
  )
  
  (:goal
    (or
      (and
        (on-ground block1)
        (block-above block2 block1)
        (block-above block3 block2)
      )
      
      (and
        (on-ground block2)
        (block-above block1 block2)
        (block-above block3 block1)
      )
      
      (and
        (on-ground block3)
        (block-above block1 block3)
        (block-above block2 block1)
      )
      
      (and
        (on-ground block1)
        (block-above block3 block1)
        (block-above block2 block3)
      )
      
      (and
        (on-ground block2)
        (block-above block3 block2)
        (block-above block1 block3)
      )
      
      (and
        (on-ground block3)
        (block-above block2 block3)
        (block-above block1 block2)
      )
    )
  )
)