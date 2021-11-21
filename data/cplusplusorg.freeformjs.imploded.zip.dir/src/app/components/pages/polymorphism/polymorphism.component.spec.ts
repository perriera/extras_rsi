/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { PolymorphismComponent } from './polymorphism.component';

describe('PolymorphismComponent', () => {
  let component: PolymorphismComponent;
  let fixture: ComponentFixture<PolymorphismComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PolymorphismComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PolymorphismComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

