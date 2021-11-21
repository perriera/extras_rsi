import { APP_BASE_HREF } from '@angular/common';
import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';

import { AboutBjarneStroustrupComponent } from './components/pages/about-bjarne-stroustrup/about-bjarne-stroustrup.component';
import { AboutBjarneStroustrupInterviewsComponent } from './components/pages/about-bjarne-stroustrup-interviews/about-bjarne-stroustrup-interviews.component';
import { AboutCppComponent } from './components/about-cpp/about-cpp.component';
import { AboutCppStandardsCommitteeComponent } from './components/pages/about-cpp-standards-committee/about-cpp-standards-committee.component';
import { AboutCppWikipediaComponent } from './components/pages/about-cpp-wikipedia/about-cpp-wikipedia.component';
import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';
import { Books1Component } from './components/pages/books-1/books-1.component';
import { Books2Component } from './components/pages/books-2/books-2.component';
import { Books3Component } from './components/pages/books-3/books-3.component';
import { Books4Component } from './components/pages/books-4/books-4.component';
import { Books5Component } from './components/pages/books-5/books-5.component';
import { Books6Component } from './components/pages/books-6/books-6.component';
import { Books7Component } from './components/pages/books-7/books-7.component';
import { Books8Component } from './components/pages/books-8/books-8.component';
import { BooksByBjarneStroupstrupComponent } from './components/pages/books-by-bjarne-stroupstrup/books-by-bjarne-stroupstrup.component';
import { CStandards1Component } from './components/pages/c-standards-1/c-standards-1.component';
import { CStandards2Component } from './components/pages/c-standards-2/c-standards-2.component';
import { CStandards3Component } from './components/pages/c-standards-3/c-standards-3.component';
import { CompatibilityComponent } from './components/pages/compatibility/compatibility.component';
import { CppBooksComponent } from './components/pages/cpp-books/cpp-books.component';
import { CriticismComponent } from './components/pages/criticism/criticism.component';
import { EtymologyComponent } from './components/pages/etymology/etymology.component';
import { EvolutionComponent } from './components/pages/evolution/evolution.component';
import { ExceptionHandlingComponent } from './components/pages/exception-handling/exception-handling.component';
import { FrequentlyRequestedPapers1Component } from './components/pages/frequently-requested-papers-1/frequently-requested-papers-1.component';
import { FrequentlyRequestedPapers2Component } from './components/pages/frequently-requested-papers-2/frequently-requested-papers-2.component';
import { FrequentlyRequestedPapers3Component } from './components/pages/frequently-requested-papers-3/frequently-requested-papers-3.component';
import { FrequentlyRequestedPapers4Component } from './components/pages/frequently-requested-papers-4/frequently-requested-papers-4.component';
import { FrequentlyRequestedPapersComponent } from './components/pages/frequently-requested-papers/frequently-requested-papers.component';
import { HistoryComponent } from './components/pages/history/history.component';
import { HomeComponent } from './components/home/home.component';
import { LambdaExpressionsComponent } from './components/pages/lambda-expressions/lambda-expressions.component';
import { LanguageComponent } from './components/pages/language/language.component';
import { ObjectStorageComponent } from './components/pages/object-storage/object-storage.component';
import { ObjectsComponent } from './components/pages/objects/objects.component';
import { OldHome2Component } from './components/demo/old-home-2/old-home-2.component';
import { OldHomeComponent } from './components/demo/old-home/old-home.component';
import { OperatorsAndOperatorOverloadingComponent } from './components/pages/operators-and-operator-overloading/operators-and-operator-overloading.component';
import { PhilosophyComponent } from './components/pages/philosophy/philosophy.component';
import { PolymorphismComponent } from './components/pages/polymorphism/polymorphism.component';
import { PublicationsComponent } from './components/pages/publications/publications.component';
import { StandardLibraryComponent } from './components/pages/standard-library/standard-library.component';
import { StandardizationComponent } from './components/pages/standardization/standardization.component';
import { StroustrupHomeComponent } from './components/pages/stroustrup-home/stroustrup-home.component';
import { StroustrupWikiComponent } from './components/pages/stroustrup-wiki/stroustrup-wiki.component';
import { SuccessComponent } from './components/demo/success/success.component';
import { TechnicalReportsComponent } from './components/pages/technical-reports/technical-reports.component';
import { TemplatesComponent } from './components/pages/templates/templates.component';

@NgModule({
  declarations: [
    AboutBjarneStroustrupComponent,
    AboutBjarneStroustrupInterviewsComponent,
    AboutCppComponent,
    AboutCppStandardsCommitteeComponent,
    AboutCppWikipediaComponent,
    AppComponent,
    Books1Component,
    Books2Component,
    Books3Component,
    Books4Component,
    Books5Component,
    Books6Component,
    Books7Component,
    Books8Component,
    BooksByBjarneStroupstrupComponent,
    CStandards1Component,
    CStandards2Component,
    CStandards3Component,
    CompatibilityComponent,
    CppBooksComponent,
    CriticismComponent,
    EtymologyComponent,
    EvolutionComponent,
    ExceptionHandlingComponent,
    FrequentlyRequestedPapers1Component,
    FrequentlyRequestedPapers2Component,
    FrequentlyRequestedPapers3Component,
    FrequentlyRequestedPapers4Component,
    FrequentlyRequestedPapersComponent,
    HistoryComponent,
    HomeComponent,
    LambdaExpressionsComponent,
    LanguageComponent,
    ObjectStorageComponent,
    ObjectsComponent,
    OldHome2Component,
    OldHomeComponent,
    OperatorsAndOperatorOverloadingComponent,
    PhilosophyComponent,
    PolymorphismComponent,
    PublicationsComponent,
    StandardLibraryComponent,
    StandardizationComponent,
    StroustrupHomeComponent,
    StroustrupWikiComponent,
    SuccessComponent,
    TechnicalReportsComponent,
    TemplatesComponent,
  ],
  imports: [
    AppRoutingModule,
    BrowserModule,
    RouterModule,
  ],
  providers: [
    {'useValue':'/','provide':'APP_BASE_HREF'},
  ],
  bootstrap: [
    AppComponent,
  ],
})
export class AppModule { }

